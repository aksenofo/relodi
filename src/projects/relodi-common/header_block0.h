/*
 *  Created on: Aug 17, 2023
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <cstdint>
#include <istream>
#include <memory>
#include <relodi-common.h>

namespace relodi::common
{
class Block0
{
public:
#pragma pack(push, 1)
    struct header_t {
        uint32_t unknown0[5];
        uint32_t blocksize;  // Размер блока, 512/1024...
        uint32_t blockcount; // Общее количество блоков текущего файла
        uint32_t unknown1[2];
        uint32_t zero[119];
    };
#pragma pack(pop)

public:
    Block0(std::istream& is);

    const header_t& header() const noexcept
    {
        return *m_header;
    }

private:
    std::unique_ptr<header_t> m_header;
};

} // namespace relodi::common
