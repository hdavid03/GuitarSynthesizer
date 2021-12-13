/*
  ==============================================================================

    WarpedIIRFilter.cpp
    Created: 11 Dec 2021 2:23:33am
    Author:  hdavid03

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WarpedIIRFilter.h"

//==============================================================================
const size_t WarpedIIRFilter::degree = 480;

WarpedIIRFilter::WarpedIIRFilter()
{
    auxiliaryArray.resize(degree);
    std::fill(auxiliaryArray.begin(), auxiliaryArray.end(), 0.0);
}

WarpedIIRFilter::~WarpedIIRFilter()
{
}

double WarpedIIRFilter::filterSample(double inputSample)
{
    auto outputSample = 0.0;
    auto input = inputSample;

    for (size_t i = 0; i < degree; i++)
    {
        input -= sigma[i + 1] * auxiliaryArray[i];
    }
    auto temporary = auxiliaryArray[0];
    auxiliaryArray[0] = input / sigma[0];
    outputSample = auxiliaryArray[0] * beta[0];

    for (size_t i = 1; i < degree; i++)
    {
        auto swap = auxiliaryArray[i];
        auxiliaryArray[i] = lambda * (auxiliaryArray[i] - auxiliaryArray[i - 1]) + temporary;
        temporary = swap;
        outputSample += auxiliaryArray[i] * beta[i];
    }
    return outputSample;
}

void WarpedIIRFilter::filterBuffer(juce::AudioBuffer<double>& buffer)
{
    auto numOfSamples = buffer.getNumSamples();

    auto src = buffer.getReadPointer(0);
    for (auto i = 0; i < numOfSamples; ++i)
    {
        double newValue = filterSample(src[i]);
        buffer.setSample(0, i, newValue);
        buffer.setSample(1, i, newValue);
    }
}

constexpr size_t WarpedIIRFilter::getDegree()
{
    return degree;
}

void WarpedIIRFilter::initialize()
{
    std::fill(auxiliaryArray.begin(), auxiliaryArray.end(), 0.0);
}
