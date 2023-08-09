/*
 *  Created on: Oct 27, 2018
 *      Author: Alexander Ksenofontov
 */

#include "base64_encoder.h"

namespace base64
{

const uint32_t rfc3548_enc_map[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/'
};

const uint32_t rfc4648_enc_map[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '-', '_'
};

const int32_t base64_dec_map[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, 62, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,

    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

//-------------------------------------------------------------------------
char* encode(char* dst, const char* src, unsigned length, bool pad, const uint32_t* tbl)
{
    while (length > 2) {
        const unsigned c1 = (unsigned char)(*src++);
        const unsigned c2 = (unsigned char)(*src++);
        const unsigned c3 = (unsigned char)(*src++);

        *dst++ = tbl[(c1 >> 2) & 0x3F];
        *dst++ = tbl[(((c1 & 3) << 4) + (c2 >> 4)) & 0x3F];
        *dst++ = tbl[(((c2 & 0x0F) << 2) + (c3 >> 6)) & 0x3F];
        *dst++ = tbl[c3 & 0x3F];

        length -= 3;
    }

    if (length > 0) {
        const unsigned c1 = (unsigned char)(*src++);
        const unsigned c2 = (length == 2) ? (unsigned char)(*src) : 0;

        *dst++ = tbl[(c1 >> 2) & 0x3F];
        *dst++ = tbl[(((c1 & 3) << 4) + (c2 >> 4)) & 0x3F];

        if (length == 2) {
            *dst++ = tbl[((c2 & 0x0F) << 2) & 0x3F];
        } else {
            if (pad) {
                *dst++ = '=';
            }
        }

        if (pad) {
            *dst++ = '=';
        }
    }

    return dst;
}

//-------------------------------------------------------------------------
char* encode(char* dst, const char* src, unsigned length, bool pad)
{
    return encode(dst, src, length, pad, rfc3548_enc_map);
}

//-------------------------------------------------------------------------
char* encode_url(char* dst, const char* src, unsigned length)
{
    return encode(dst, src, length, false, rfc4648_enc_map);
}

//-------------------------------------------------------------------------
char* decode(char* dst, const char* src, unsigned length)
{
    const char* src_start = src;

    length = length_wo_padding(src, length);

    while (length > 3) {
        int32_t b = base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }

        dst[2] = (unsigned char)(b);
        b >>= 8;
        dst[1] = (unsigned char)(b);
        b >>= 8;
        *dst = (unsigned char)(b);

        dst += 3;
        length -= 4;
    }

    switch (length) {
    case 0:;
        break;
    default:
        throw bad_format_exception(unsigned(src - src_start));
    case 2: {
        int32_t b = base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        *dst++ = (unsigned char)(b >> 4);
        break;
    }
    case 3: {
        int32_t b = base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        b = (b << 6) + base64_dec_map[(unsigned char)(*src++)];
        if (b < 0) {
            throw bad_format_exception(unsigned(src - src_start) - 1);
        }
        *dst++ = (unsigned char)(b >> 10);
        *dst++ = (unsigned char)(b >> 2);
        break;
    }
    }

    return dst;
}

} // namespace base64
