/*
  ==============================================================================

    FractionalDelayFilter.h
    Created: 11 Dec 2021 2:22:09am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once
#include <cstddef>

//==============================================================================
/*
*/

class FractionalDelayFilter
{
public:
    FractionalDelayFilter();
    void initialize(double, size_t);
    double filterSample(double);
private:
    double a = 0.0;
    double y = 0.0;
    double x = 0.0;
};
