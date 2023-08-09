/*
 *  Created on: Oct 26, 2018
 *      Author: Alexander Ksenofontov
 */

#include "common.h"

#include <algorithm>

void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}

void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

std::string ltrimed(std::string s)
{
    auto rs = s;
    ltrim(rs);
    return rs;
}

std::string rtrimed(std::string s)
{
    auto rs = s;
    rtrim(rs);
    return rs;
}

std::string trimed(std::string s)
{
    auto rs = s;
    trim(rs);
    return rs;
}

void parse_string(const std::string& str, std::function<void(char type, int id, int code)> fn)
{
    enum eStatus {
        cChar,
        cType,
        cId,
        cCode
    };
    eStatus inside = cChar;
    int id, code;
    char type;

    auto clean = [&]() {
        code = 0;
        id = 0;
        type = 0;
    };

    clean();

    for (auto x : str) {
        if (inside == cChar && x == '#') {
            clean();
            inside = cType;
            continue;
        }
        if (inside == cType && (x == 'O' || x == 'P' || x == 'o' || x == 'p')) {
            type = x;
            inside = cId;
            continue;
        }
        if (inside == cId && (x >= '0' && x <= '9')) {
            id *= 10;
            id += (x - '0');
            continue;
        }
        if (inside == cId && x == ':') {
            inside = cCode;
            continue;
        }
        if (inside == cCode && (x >= '0' && x <= '9')) {
            code *= 10;
            code += (x - '0');
            continue;
        }
        inside = cChar;
        if (type > 0) {
            fn(type, id, code);
            clean();
        }
    }
    if (type > 0) {
        fn(type, id, code);
        clean();
    }
}
