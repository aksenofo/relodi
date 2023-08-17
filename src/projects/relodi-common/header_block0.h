/*
 *  Created on: Aug 17, 2023
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <cstdint>
#include <istream>
#include <memory>

namespace relodi::common
{

namespace utility
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

} // namespace utility

class Block0
{
public:
#pragma pack(push, 1)
    struct header_0 {
        uint32_t unknown0[5];
        uint32_t blocksize;  // Размер блока, 512/1024...
        uint32_t blockcount; // Общее количество блоков текущего файла
        uint32_t unknown1[2];
        uint32_t zero[119];
    };
#pragma pack(pop)

public:

    Block0(std::iostream& stream)
    : header_(std::make_unique<header_0>())
    {
        stream.read(reinterpret_cast<char*>(header_.get()), sizeof(header_0));
        utility::correct(header_->blocksize);
        utility::correct(header_->blockcount);
    }

private:
    std::unique_ptr<header_0> header_;
};

} // namespace relodi::common
