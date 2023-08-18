/*
 *  Created on: Aug 17, 2023
 *      Author: Alexander Ksenofontov
 */

#include <header_block0.h>

namespace relodi::common
{

Block0::Block0(std::istream& is)
: m_header(std::make_unique<header_t>())
{
    is.read(reinterpret_cast<char*>(m_header.get()), sizeof(header_t));
    utility::correct(m_header->blocksize);
    utility::correct(m_header->blockcount);
}

} // namespace relodi::common
