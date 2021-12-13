/*
  ==============================================================================

    LossFilter.cpp
    Created: 11 Dec 2021 2:22:27am
    Author:  hdavid03

  ==============================================================================
*/

#include "LossFilter.h"

//==============================================================================
LossFilter::LossFilter()
{
}

double LossFilter::filterSample(double sample)
{
    y = g * (1 + a) * sample - y * a;
    return y;
}

void LossFilter::initialize()
{
    y = 0;
}
