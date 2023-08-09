/*
 *  Created on: Oct 3, 2021
 *      Author: Alexander Ksenofontov
 */


#include <chrono>
#include <functional>
#include <iostream>
#include <random>

namespace
{
struct Generator : public std::default_random_engine {
    Generator()
    : std::default_random_engine()
    {
        seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
    }
};  
} // namespace
    
static Generator generator;
    
static std::uniform_int_distribution<uint64_t>
    distribution(0, 18446744073709551615ULL - 100ULL);


std::string random_id(const size_t& size)
{
    std::string rc;
    rc.reserve(size);
    auto calc = [&rc]() {
        const unsigned char uc = distribution(generator) & 0xFF;
        const unsigned char h1 = (uc & 0xF) + 'A';
        const unsigned char h2 = ((uc & 0xF0) >> 4) + 'A';
        rc += h1;
        rc += h2;
    };
    for (size_t t = 0; t < size / 2; t++) {
        calc();
    }
    if (size % 2) {
        calc();
    }

    return rc;
}
