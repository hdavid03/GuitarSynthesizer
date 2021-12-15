/*
  ==============================================================================

    LossFilter.cpp
    Created: 11 Dec 2021 2:22:27am
    Author:  hdavid03

  ==============================================================================
*/

#include "LossFilter.h"
#include <complex>

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

double LossFilter::getPhaseDelay(double sampleRate, double noteFrequency)
{
    const double pi2 = 2 * std::acos(-1);
    const std::complex<double> j(0, 1);
    const std::complex<double> aComplex(a, 0);
    const std::complex<double> one(1, 0);
    const std::complex<double> hjw = g * (one + aComplex) / (one + aComplex * std::exp(-j * noteFrequency * pi2 / sampleRate));

    return std::atan2(hjw.imag(), hjw.real());
}
