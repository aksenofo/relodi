/*
 *  Created on: Aug 18, 2023
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <cstdint>

namespace relodi::common::utility
{
static bool need_to_correct = false;

class ByteOrder {
public:
    static void correct(uint16_t& val)
    {
        if (need_to_correct) {
            auto t = val;
            val = (t >> 8) | (t << 8);
        }
    }

    static void correct(uint32_t& val)
    {
        if (need_to_correct) {
            auto t = val;
            val = ((t >> 24) & 0xff) |
                ((t << 8) & 0xff0000) |
                ((t >> 8) & 0xff00) |
                ((t << 24) & 0xff000000);
        }
    }

    static void correct(uint64_t& ull)
    {
        ull = (ull >> 56) |
            ((ull<<40) & 0x00FF000000000000) |
            ((ull<<24) & 0x0000FF0000000000) |
            ((ull<<8) & 0x000000FF00000000) |
            ((ull>>8) & 0x00000000FF000000) |
            ((ull>>24) & 0x0000000000FF0000) |
            ((ull>>40) & 0x000000000000FF00) |
            (ull << 56);
    }
};

inline uint16_t calcChSum(const uint8_t* buffer, uint64_t size, uint16_t check )
{
    uint64_t sum = 0;
        
    for (uint64_t i = 0; i < size / 8; ++i, buffer += 8)
        sum ^= *(reinterpret_cast<const uint64_t*>(buffer));
    sum ^= (sum >> 32);
    sum ^= (sum >> 16);
    sum ^= check;

    return static_cast<uint16_t>(sum);
}


} // namespace relodi::common::utility
