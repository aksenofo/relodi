/*
 *  Created on: Oct 27, 2018
 *      Author: Alexander Ksenofontov
 */

#pragma once
#include <string>

namespace base62
{

class encoder
{
public:
    template<typename int_type>
    static char* int_to_text(char* buf, int_type value);

    template<typename int_type>
    static const char* text_to_int(const char* buf, const char* end,
        int_type& value);

private:
    static const char itob[62];
    static const unsigned btoi[256];
};

template<typename int_type>
char* encoder::int_to_text(char* buf, int_type value)
{
    if (value == 0) {
        *buf++ = itob[0];
    } else {
        do {
            unsigned digit = value % 62;
            value /= 62;
            *buf++ = itob[digit];
        } while (value != 0);
    }
    return buf;
}

template<typename int_type>
const char* encoder::text_to_int(const char* buf, const char* end,
    int_type& value)
{
    int_type v = 0, scale = 1;

    do {
        int_type digit = btoi[*(unsigned char*)buf];
        if (digit >= 62) {
            break;
        }
        v += digit * scale;
        scale *= 62;
        buf += 1;
    } while (buf != end);

    value = v;

    return buf;
}

template<typename type>
char* encode(char* buf, const type& value)
{
    return encoder::int_to_text(buf, value);
}

template<typename type>
const char* decode(const char* start, const char* stop, type& value)
{
    return encoder::text_to_int(start, stop, value);
}

template<typename type>
const char* decode(const std::string& buf, type& value)
{
    return encoder::text_to_int(&*buf.begin(), &*(buf.end() - 1), value);
}

} // namespace base62
