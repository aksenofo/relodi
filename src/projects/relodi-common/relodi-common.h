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

} // namespace relodi::common::utility
