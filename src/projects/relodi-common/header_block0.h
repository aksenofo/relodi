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
    struct header_0 {
        uint32_t unknown0[5];
        uint32_t blocksize;  // Размер блока, 512/1024...
        uint32_t blockcount; // Общее количество блоков текущего файла
        uint32_t unknown1[2];
        uint32_t zero[119];
    };
#pragma pack(pop)

public:
    Block0(std::istream& is)
    : m_header(std::make_unique<header_0>())
    {
        is.read(reinterpret_cast<char*>(m_header.get()), sizeof(header_0));
        utility::correct(m_header->blocksize);
        utility::correct(m_header->blockcount);
    }

    const header_0& header() const noexcept
    {
        return *m_header;
    }

private:
    std::unique_ptr<header_0> m_header;
};

} // namespace relodi::common
