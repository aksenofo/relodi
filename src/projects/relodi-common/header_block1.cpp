/*
 *  Created on: Aug 17, 2023
 *      Author: Alexander Ksenofontov
 */

#include "header_block1.h"

#include "relodi-common.h"

#include <format.h>
#include <stdexcept>

namespace relodi::common
{

Block1::Block1(size_t blockSize, std::istream& is)
: m_buffer(std::make_unique<uint8_t[]>(blockSize))
{
    is.read(reinterpret_cast<char*>(m_buffer.get()), blockSize);
    utility::correct(header().signature); // подпись
    utility::correct(header().blocknum);  // Номер блока
    utility::correct(header().filenum);   // Порядковый номер
    utility::correct(header().offset);    // В позиции, с которой начинается первая запись повтора текущего блока, старший бит отбрасывается
    utility::correct(header().checksum);  // Контрольная сумма блока, обновляемая при записи
    if (header().signature != signature)
        throw std::runtime_error(format("Invalid signature %1 (expected %2)", header().signature, signature));
    auto cs = utility::calcChSum(m_buffer.get(), blockSize, header().checksum);
    if (cs != header().checksum)
        throw std::runtime_error(format("Invalid checksum %1 (expected %2)", header().checksum, cs));
}

} // namespace relodi::common
