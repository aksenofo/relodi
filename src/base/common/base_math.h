/*
 *  Created on: Jun 16, 2019
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <stddef.h>

namespace bm
{
namespace _malarkey_
{
constexpr auto count_args() -> size_t
{
    return 0;
}

template<typename T1, typename... Ti>
constexpr auto count_args(T1, Ti... xi) -> size_t
{
    return 1 + count_args(xi...);
}
} // namespace _malarkey_

template<typename T>
constexpr auto sum(T first)
{
    return first;
}

template<typename T, typename... Args>
constexpr auto sum(T first, Args... args)
{
    return first + sum(args...);
}

template<class... T>
constexpr auto average(T... xi)
{
    return sum(xi...) / _malarkey_::count_args(xi...);
}

} // namespace bm
