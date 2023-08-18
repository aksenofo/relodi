/*
 *  Created on: Aug 18, 2023
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <cstdint>

namespace relodi::common::utility
{
static bool need_to_correct = false;
inline void correct(uint16_t& val)
{
    if (need_to_correct) {
        auto t = val;
        val = (t >> 8) | (t << 8);
    }
}

inline void correct(uint32_t& val)
{
    if (need_to_correct) {
        auto t = val;
        val = ((t >> 24) & 0xff) |
            ((t << 8) & 0xff0000) |
            ((t >> 8) & 0xff00) |
            ((t << 24) & 0xff000000);
    }
}

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
