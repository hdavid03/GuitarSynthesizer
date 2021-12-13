/*
  ==============================================================================

    FractionalDelayFilter.cpp
    Created: 11 Dec 2021 2:22:09am
    Author:  hdavid03

  ==============================================================================
*/
#include "FractionalDelayFilter.h"

//==============================================================================
FractionalDelayFilter::FractionalDelayFilter()
{
}

double FractionalDelayFilter::filterSample(double sample)
{
    y = a * sample + x - a * y;
    x = sample;
    return y;
}

void FractionalDelayFilter::initialize(double fractionedSampleNumber, size_t roundedSampleNumber)
{
    auto D = fractionedSampleNumber - 2 * roundedSampleNumber;
    a = (1 - D) / (1 + D);
    x = 0.0;
    y = 0.0;
}
