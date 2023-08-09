/*
 *  Created on: Oct 26, 2018
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include "base_math.h"

#include <algorithm>
#include <assert.h>
#include <cctype>
#include <ctype.h>
#include <functional>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <type_traits>
#include <variant>

#define assert_msg(A, TEXT) assert(TEXT&& A)

#if WIN32

#define ssize_t int

#define AND &&
#define and &&

#define OR ||
#define or ||

#endif // WIN32

template<typename T, size_t size_of>
constexpr size_t num_of_elem(T (&)[size_of])
{
    return size_of;
}

/*!
    \brief Clone container to unique_ptr<Container>
    \param[in] container - Container which should be cloned.(this is AMUST
                            case which came from sqlite_orm interface)
*/
template<typename Container>
std::unique_ptr<Container> to_unique(
    const Container& container,
    std::function<bool(const typename Container::value_type& v)> fn = [](const typename Container::value_type) { return true; })
{
    std::unique_ptr<Container> ret;
    if (container.empty())
        return ret;

    ret = std::move(std::make_unique<Container>());
    std::for_each(std::begin(container), std::end(container), [&ret, &fn](const auto& itm) {
        if (fn(itm))
            ret->emplace_back(itm);
    });
    return ret;
}


// Min, max auxillary stuff
namespace _malarkey_
{

template<typename Value, typename Payload>
class ValueMiniMaxer
{
public:
    const Value& value() const { return value_; }

    Payload& payload() { return payload_; }

    const Payload& payload() const { return payload_; }

    std::pair<Value, Payload> result() const { return { value_, payload_ }; }

    bool collected() const { return collected_; }

protected:
    ValueMiniMaxer(const Value& value)
    : value_(value)
    {
    }

    Value value_;
    Payload payload_;
    bool collected_ = false;
};

} // namespace _malarkey_

/*!
    \brief Collect the payload which is connected to minimum value
    \param[in] typename Value - value type ( must have operator < )
    \param[in] typename Payload - payload to be collected

*/
template<typename Value, typename Payload = Value>
class ValueMinimizer : public _malarkey_::ValueMiniMaxer<Value, Payload>
{
public:
    ValueMinimizer()
    : _malarkey_::ValueMiniMaxer<Value, Payload>(std::numeric_limits<Value>::max())
    {
    }
    void check(const Value& value)
    {
        check(value, value);
    }
    void check(const Value& value, Payload payload)
    {
        if (value < _malarkey_::ValueMiniMaxer<Value, Payload>::value_) {
            _malarkey_::ValueMiniMaxer<Value, Payload>::value_ = value;
            _malarkey_::ValueMiniMaxer<Value, Payload>::payload_ = payload;
            _malarkey_::ValueMiniMaxer<Value, Payload>::collected_ = true;
        }
    }
    void operator()(const Value& value, Payload payload)
    {
        check(value, payload);
    }
    void operator()(const Value& value)
    {
        check(value);
    }
};

/*!
    \brief Collect the payload which is connected to maximum value
    \param[in] typename Value - value type ( must have operator < )
    \param[in] typename Payload - payload to be collected

*/
template<typename Value, typename Payload = Value>
class ValueMaximizer : public _malarkey_::ValueMiniMaxer<Value, Payload>
{
public:
    ValueMaximizer()
    : _malarkey_::ValueMiniMaxer<Value, Payload>(std::numeric_limits<Value>::min())
    {
    }
    void check(const Value& value)
    {
        check(value, value);
    }
    void check(const Value& value, Payload payload)
    {
        if (value > _malarkey_::ValueMiniMaxer<Value, Payload>::value_) {
            _malarkey_::ValueMiniMaxer<Value, Payload>::value_ = value;
            _malarkey_::ValueMiniMaxer<Value, Payload>::payload_ = payload;
            _malarkey_::ValueMiniMaxer<Value, Payload>::collected_ = true;
        }
    }
    void operator()(const Value& value, Payload payload)
    {
        check(value, payload);
    }
    void operator()(const Value& value)
    {
        check(value);
    }
};

/*!
    \brief Format in printf style and print to string
    \param[in] format - in printf style
    \param[in] args - args to be printed

*/
template<typename... Args>
std::string sformat(const char* format, Args... args)
{
    int length = std::snprintf(nullptr, 0, format, args...);
    assert(length >= 0);
    std::unique_ptr<char[]> buf(new char[length + 1]);
    std::snprintf(buf.get(), length + 1, format, args...);
    return buf.get();
}

/*!
    \brief Left trim string
    \param[in] S - string to be trimmed.

*/
void ltrim(std::string& s);

/*!
    \brief Right trim string
    \param[in] S - string to be trimmed.

*/
void rtrim(std::string& s);

/*!
    \brief Left and Right trim string
    \param[in] S - string to be trimmed.

*/
void trim(std::string& s);

/*!
    \brief Left trim string
    \param[in] S - string to be trimmed.
    \return trimmed string

*/
std::string ltrimed(std::string s);

/*!
    \brief Right trim string
    \param[in] S - string to be trimmed.
    \return trimmed string
*/
std::string rtrimed(std::string s);

/*!
    \brief Left and Right trim string
    \param[in] S - string to be trimmed.
    \return trimmed string
*/
std::string trimed(std::string s);

bool match_text(const std::string& text, const std::string& match);

void parse_string(const std::string& str, std::function<void(char type, int id, int code)> fn);

/*!
    \brief Convert container to string with delimiter
    \param[in] begin/end - Container iterator (vector, deque, ...).
    \param[in] fn - Transformation function.
    \param[in] delim - string delimiter.
    \return result string
*/
template<typename Iterator>
std::string container2string(Iterator begin, Iterator end,
    std::function<std::string(const typename Iterator::value_type&)> fn,
    std::string delim = ",")
{
    if (end == begin)
        return "";

    std::ostringstream vts;
    auto pre_end = end - 1;
    std::transform(begin, pre_end, std::ostream_iterator<std::string>(vts),
        [&](auto& pl) {
            return fn(pl) + delim;
        });
    std::transform(pre_end, end, std::ostream_iterator<std::string>(vts),
        [&](auto& pl) {
            return fn(pl);
        });
    return vts.str();
}

namespace _malarkey_
{

template<typename T>
struct HasPushBack {
    typedef char yes[1];
    typedef char no[2];

    template<class U, void (U::*)(const typename U::value_type&) = &U::push_back>
    struct MethodTraits;

    template<typename U>
    static yes& _has(MethodTraits<U>*);

    template<typename>
    static no& _has(...);

    static const bool value = sizeof(_has<T>(0)) == sizeof(yes);
};
} // namespace _malarkey_

template<typename Container, typename Iterator>
Container array2container(Iterator begin, Iterator end,
    std::function<bool(const typename Iterator::value_type&)> fn)
{
    Container rc;
    typename Container::value_type value;
    constexpr static bool has_push_back = _malarkey_::HasPushBack<Container>::value ||
        std::is_same<Container, std::string>::value;

    constexpr static bool has_push_back_value_type =
        _malarkey_::HasPushBack<typename Container::value_type>::value ||
        std::is_same<typename Container::value_type, std::string>::value;
    ;

    std::for_each(begin, end, [&](const typename Iterator::value_type& v) {
        if (fn(v)) {
            if constexpr (has_push_back)
                rc.push_back(value);
            else
                rc.insert(value);

            value = typename Container::value_type();
        } else {

            if constexpr (has_push_back_value_type)
                value.push_back(v);
            else
                value.insert(v);
        }
    });
    if (!value.empty()) {
        if constexpr (has_push_back)
            rc.push_back(value);
        else
            rc.insert(value);
    }
    return rc;
}

template<typename Container, typename Iterator>
Container trim(Iterator begin, Iterator end,
    std::function<bool(const typename Iterator::value_type&)> fn)
{
    Container rc;
    constexpr static bool has_push_back = _malarkey_::HasPushBack<Container>::value ||
        std::is_same<Container, std::string>::value;

    std::for_each(begin, end, [&](const typename Iterator::value_type& v) {
        if (fn(v)) {
            if constexpr (has_push_back) {
                rc.push_back(v);
            } else {
                rc.insert(v);
            }
        }
    });
    return rc;
}


template<typename Op, typename... Type>
void cycle_operation(size_t number, const Op& fn, Type&&... operand)
{
    while (number--)
        fn(std::forward<Type>(operand)...);
}
