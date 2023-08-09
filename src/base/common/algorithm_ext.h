/*
 *  Created on: Jul 5, 2019
 *      Author: Alexander Ksenofontov
 */

#pragma once

/*!
        \brief Callback for any container in segment style
        Assume, we have vector(any container) with points (p1, p2, p3, p4)
        which are presenting array of segments ({p1,p2}, {p2, p3}, {p3, p4}).
        So, we get a number of callback with fn({p1,p2}), fn({p2,p3}), .....
        \param[in] start - start iterator
        \param[in] stop - start iterator
        \param[in] fn - acllback function

*/
template<typename Iterator, typename Function>
void for_each_segment(Iterator start,
    Iterator stop,
    Function fn)
{
    stop--;
    for (auto it = start; it < stop; it++) {
        fn(*it, *(it + 1));
    }
}
