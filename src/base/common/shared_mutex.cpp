/*
 *  Created on: Jul 20, 2019
 *      Author: Alexander Ksenofontov
 */

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

class shared_mutex
{

public:
    void lock_type(int typ)
    {
        thread_local int type = 0;
        if (typ == type)
            return;
        if (typ == 0)
            type = typ;
        else if (type == 0) {
            type = typ;
        } else
            throw std::runtime_error("Lock type (lock/lock_shared) mixed up");
    }

    int thread_local_count(int delta)
    {
        thread_local int count = 0;
        auto old = count;
        count += delta;
        if (count < 0)
            throw std::runtime_error("Invalid lock counter");
        return old;
    }

    void lock()
    {
        lock_type(-1);
        if (thread_local_count(1) != 0)
            return;

        int value;
        do {
            value = 0; 
        } while (!refcouter_.compare_exchange_weak(value, -1, std::memory_order_acquire));
    }

    void unlock()
    {
        lock_type(-1);
        if (thread_local_count(-1) != 1) {
            return;
        }
        refcouter_.store(0, std::memory_order_release);
        lock_type(0);
    }

    void lock_shared()
    {
        lock_type(1);
        if (thread_local_count(1) != 0)
            return;

        int value;
        do {
            do {
                value = refcouter_.load(std::memory_order_relaxed);
            } while (value == -1);
        } while (!refcouter_.compare_exchange_weak(value, value + 1, std::memory_order_acquire));
    }

    void unlock_shared()
    {
        lock_type(1);
        if (thread_local_count(-1) != 1) {
            return;
        }
        refcouter_.fetch_sub(1, std::memory_order_relaxed);
        lock_type(0);
    }

private:
    std::atomic<int> refcouter_{ 0 };
};
