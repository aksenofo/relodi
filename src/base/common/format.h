/*
 *  Created on: March 9, 2022
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <vector>

class BoolAsString
{
public:
    BoolAsString(bool flag)
    : m_flag(flag)
    {
    }

    bool m_flag;
};

inline std::string to_string_help(const BoolAsString& bas)
{
    return bas.m_flag ? "True" : "False";
}

class CodeTextAsString
{

public:
    CodeTextAsString(int code, const std::function<const char*(int)>& fn)
    {
        m_code = code;
        m_text = fn(code);
    }

    int m_code = 0;
    std::string m_text;
};

inline std::string to_string_help(const CodeTextAsString& ctas)
{
    return std::to_string(ctas.m_code) + " " + ctas.m_text;
}

class CodeTextAsString1
{

public:
    CodeTextAsString1(int code, const std::function<std::string(int)>& fn)
    {
        m_code = code;
        m_text = fn(code);
    }

    int m_code = 0;
    std::string m_text;
};

inline std::string to_string_help(const CodeTextAsString1& ctas)
{
    return std::to_string(ctas.m_code) + " " + ctas.m_text;
}

std::string format_impl(const std::string& fmt, const std::vector<std::string>& strs);

using Bas = BoolAsString;
using Ctas = CodeTextAsString;
using Ctas1 = CodeTextAsString1;

inline std::string to_string_help(const std::error_code& ec)
{
    return std::string("(") + std::to_string(ec.value()) + std::string(") ") + ec.message();
}

inline std::string to_string_help(const std::string& str)
{
    return str;
}

inline std::string to_string_help(const char* str)
{
    return str;
}

inline std::string to_string_help(const std::string_view& v)
{
    return std::string(v);
}

template<typename Type>
std::string to_string_help(const Type& v)
{
    return std::to_string(v);
}

template<typename Arg, typename... Args>
inline std::string format_impl(const std::string& fmt, std::vector<std::string>& strs, Arg&& arg, Args&&... args)
{
    strs.push_back(to_string_help(std::forward<Arg>(arg)));
    return format_impl(fmt, strs, std::forward<Args>(args)...);
}

inline std::string format(const std::string& fmt)
{
    return fmt;
}

template<typename Arg, typename... Args>
inline std::string format(const std::string& fmt, Arg&& arg, Args&&... args)
{
    std::vector<std::string> strs;
    return format_impl(fmt, strs, std::forward<Arg>(arg), std::forward<Args>(args)...);
}
