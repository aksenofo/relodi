/*
 *  Created on: Oct 27, 2018
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include "stdint.h"

#include <stdexcept>
#include <string>

namespace base64
{

/**
 * Exception raised when encoding format problem detected.
 */
class bad_format_exception : public std::runtime_error
{
public:
    /**
	 * Initialize exception object.
	 * @param position position of problem in input string.
	 */
    bad_format_exception(unsigned position)
    : std::runtime_error(mk_text(position))
    {
        position_ = position;
    }

    unsigned position(void) const { return position_; }

private:
    static std::string mk_text(const unsigned& position)
    {
        char buf[128];
        sprintf(buf, "Failed in position:%u", position);
        return buf;
    }
    unsigned position_;
};

/**
 * Determine length of encoded string.
 * @param length number of bytes in string.
 * @return number of bytes in the corresponding encoded string.
 */
inline unsigned encode_length(unsigned length, bool pad)
{
    unsigned l = ((length + 2) / 3) * 4;
    if (!pad) {
        unsigned r = length % 3;
        if (r > 0) {
            if (r == 2)
                l -= 1;
            else
                l -= 2;
        }
    }
    return l;
}

/**
 * Encode byte sequence using RFC3548 (base64).
 * @param dst address of buffer for encoded data.
 * @param src address of data to be coded.
 * @param length number of bytes to encode.
 * @param pad @c true if the encoded data should be padded with '='.
 * @return address in output buffer after encoded data.
 */
char* encode(char* dst, const char* src, unsigned length, bool pad);

/**
 * Encode string using RFC3548 (base64).
 * @param src string with data to be coded.
 * @param pad @c true if the encoded data should be padded with '='.
 * @return string with encoded data.
 */
inline std::string encode(std::string src, bool pad)
{
    size_t size = encode_length(static_cast<unsigned>(src.size()), pad);
    char* data = reinterpret_cast<char*>(alloca(size));
    encode(data, src.data(), static_cast<unsigned>(src.size()), pad);
    return std::string(data, size);
}

/**
 * Encode byte sequence using RFC4648 (url-safe base64).
 * @param dst address of buffer for encoded data.
 * @param src address of data to be coded.
 * @param length number of bytes to encode.
 * @return address in output buffer after encoded data.
 */
char* encode_url(char* dst, const char* src, unsigned length);

/**
 * Encode string using RFC4648 (url-safe base64).
 * @param src string with data to be coded.
 * @return string with encoded data.
 */
inline std::string encode_url(std::string src)
{
    unsigned size = encode_length(static_cast<unsigned>(src.size()), false);
    char* data = reinterpret_cast<char*>(alloca(size));
    encode_url(data, src.data(), static_cast<unsigned>(src.size()));
    return std::string(data, size);
}

/**
 * Compute length of encoded string without padding symbols.
 * @param src address of encoded data.
 * @param length number of bytes in string.
 * @return length of input without padding symbols at the end.
 */
inline unsigned length_wo_padding(const char* src, unsigned length)
{
    if (length > 0 && src[length - 1] == '=') {
        length -= 1;
        if (length > 0 && src[length - 1] == '=')
            length -= 1;
    }
    return length;
}

/**
 * Determine length of decoded string.
 * @param src address of encoded data.
 * @param length number of bytes in string.
 * @return number of bytes in the corresponding decoded string.
 */
inline unsigned decode_length(const char* src, unsigned length)
{
    length = length_wo_padding(src, length);
    unsigned l = (length / 4) * 3;
    unsigned lr = length & 3;
    if (lr > 0)
        l += (lr == 3) ? 2 : 1;
    return l;
}

/**
 * @brief Decode base64 string.
 * @param dst the start of output buffer.
 * @param src address of encoded data.
 * @param length number of bytes in string.
 * @return address in output buffer after decoded string.
 */
char* decode(char* dst, const char* src, unsigned length);

/**
 * @brief Decode base64 string.
 * @param src encoded data.
 * @return decoded string.
 */
inline std::string decode(std::string src)
{
    size_t size = decode_length(src.data(), static_cast<unsigned>(src.size()));
    char* data = reinterpret_cast<char*>(alloca(size));
    decode(data, src.data(), static_cast<unsigned>(src.size()));
    return std::string(data, size);
}

} // namespace base64
