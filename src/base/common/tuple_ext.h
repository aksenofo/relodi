/*
 *  Created on: May 27, 2019
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <tuple>

namespace _malarkey_
{
template<int index, typename Func, typename... Args>
struct iterate_tuple {
    static void next(std::tuple<Args...>& t, Func fn)
    {
        iterate_tuple<index - 1, Func, Args...>::next(t, fn);
        fn(index, std::get<index>(t));
    }
};

template<typename Func, typename... Args>
struct iterate_tuple<0, Func, Args...> {
    static void next(std::tuple<Args...>& t, Func fn)
    {
        fn(0, std::get<0>(t));
    }
};

template<typename Func, typename... Args>
struct iterate_tuple<-1, Func, Args...> {
    static void next(std::tuple<Args...>& t, Func fn) {}
};
} // namespace _malarkey_

template<typename Func, typename... Args>
void foreach_tuple(std::tuple<Args...>& t, Func fn)
{
    _malarkey_::iterate_tuple<std::tuple_size<std::tuple<Args...>>::value - 1,
        Func, Args...>::next(t, fn);
}
