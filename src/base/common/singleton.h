/*
 *  Created on: Jan 23, 2019
 *      Author: Alexander Ksenofontov
 */

#pragma once

template<class T>
class singleton
{
    T payload_;
    singleton<T>(singleton<T> const&) = delete;
    singleton<T>& operator=(singleton<T> const&) = delete;
    singleton<T>() {}

public:
    static auto instance() -> T*
    {
        static singleton<T> st;
        return &st.payload_;
    }
};
