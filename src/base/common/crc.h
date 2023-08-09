/*
 *  Created on: Oct 26, 2015
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <limits>
#include <stdint.h>
#include <stdio.h>

namespace crc
{

uint16_t get16(const unsigned char* buf, size_t len,
    uint16_t init = std::numeric_limits<uint16_t>::max());

uint32_t get32(const unsigned char* buf, size_t len,
    uint32_t init = std::numeric_limits<uint32_t>::max());

} //namespace crc
