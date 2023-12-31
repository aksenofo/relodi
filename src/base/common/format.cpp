/*
 *  Created on: March 9, 2022
 *      Author: Alexander Ksenofontov
 */

#include "format.h"

std::string format_impl(const std::string& fmt, const std::vector<std::string>& strs)
{
    static constexpr char FORMAT_SYMBOL = '%';
    std::string res, buf;
    bool arg = false;

    for (int i = 0; i <= static_cast<int>(fmt.size()); ++i) {
        bool last = i == static_cast<int>(fmt.size());
        const char ch = fmt[i];
        if (arg) {
            if (ch >= '0' && ch <= '9') {
                buf += ch;
            } else {
                int num = 0;
                if (!buf.empty() && buf.length() < 10)
                    num = atoi(buf.c_str());
                if (num >= 1 && num <= static_cast<int>(strs.size()))
                    res += strs[num - 1];
                else
                    res += FORMAT_SYMBOL + buf;
                buf.clear();
                if (ch != FORMAT_SYMBOL) {
                    if (!last)
                        res += ch;
                    arg = false;
                }
            }
        } else {
            if (ch == FORMAT_SYMBOL) {
                arg = true;
            } else {
                if (!last)
                    res += ch;
            }
        }
    }
    return res;
}
