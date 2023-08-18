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

class Block1
{
    constexpr static uint32_t signature = 8705;

public:

#pragma pack(push, 1)
    struct header_t {
        uint32_t signature; // подпись
        uint32_t blocknum;  // Номер блока
        uint32_t filenum;   // Порядковый номер
        uint16_t offset;    // В позиции, с которой начинается первая запись повтора текущего блока, старший бит отбрасывается
        uint16_t checksum;  // Контрольная сумма блока, обновляемая при записи
    };
#pragma pack(pop)

public:
    Block1(size_t blockSize, std::istream& is);

    const header_t& header() const noexcept
    {
        return *reinterpret_cast<header_t*>(m_buffer.get());
    }

    header_t& header() noexcept
    {
        return *reinterpret_cast<header_t*>(m_buffer.get());
    }

private:
    std::unique_ptr<uint8_t[]> m_buffer;
};

} // namespace relodi::common
