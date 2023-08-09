/*
 *  Created on: Aug 12, 2019
 *      Author: Alexander Ksenofontov
 */

#pragma once
#include <algorithm>

/*!
    \brief Walking through semi-matrix and calling for_each
    \param[in] it_begin/it_end - Iterators for container
*/
template<typename Iterator>
void for_each_as_halfmatrix(Iterator it_begin, Iterator it_end,
    std::function<void(const typename Iterator::value_type& i1,
        const typename Iterator::value_type& i2)>
        fn)
{
    auto tit = it_begin;
    std::for_each(it_begin, it_end, [&](const typename Iterator::value_type& i1) {
        std::for_each(it_begin, tit, [&](const typename Iterator::value_type& i2) {
            fn(i1, i2);
        });
        tit++;
    });
}
