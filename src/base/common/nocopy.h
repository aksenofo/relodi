/*
 *  Created on: Oct 4, 2018
 *      Author: Alexander Ksenofontov
 */

#pragma once

class nocopy
{
protected:
    nocopy() = default;
    nocopy& operator=(const nocopy&) = delete;
    nocopy(const nocopy&) = delete;
};

class nomove
{
protected:
    nomove() = default;
    nomove& operator=(nomove&&) = delete;
    nomove(nomove&&) = delete;
};
