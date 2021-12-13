/*
  ==============================================================================

    WaveGuide.cpp
    Created: 11 Dec 2021 2:24:36am
    Author:  hdavid03

  ==============================================================================
*/
#include "WaveGuide.h"
#include <cmath>

void WaveGuide::shiftDelayLines()
{
	size_t step = lastArrayIndex - dataPointer;
	auto tmp = forwardDelayLine[dataPointer];
	forwardDelayLine[dataPointer] = reflection * backwardDelayLine[step];
	backwardDelayLine[step] = reflection * fractionalDelayFilter.filterSample(lossFilter.filterSample(tmp));
	dataPointer = dataPointer == 0 ? lastArrayIndex - 1 : dataPointer - 1;
}

WaveGuide::WaveGuide()
{
}

void WaveGuide::loadDelayLines()
{
	backwardDelayLine.resize(length);
	forwardDelayLine.resize(length);
	for (size_t i = 0; i < triggerPoint; i++)
	{
		backwardDelayLine[i] = deviation * i / (triggerPoint - 1);
	}
	for (size_t i = triggerPoint; i < length; i++)
	{
		backwardDelayLine[i] = deviation * (length - i - 1) / (length - triggerPoint);
	}
	forwardDelayLine.operator=(backwardDelayLine);
}

void WaveGuide::initialize(double midiNoteInHertz, double sampleRateInHertz)
{
	auto fraction = sampleRateInHertz / midiNoteInHertz;
	length = (size_t)fraction / 2;
	double dx = stringLengthInMeter / fraction;
	correctionMultiplier = 2 * tension / dx / sampleRateInHertz;
	lastArrayIndex = length - 1;
	dataPointer = lastArrayIndex;
	fractionalDelayFilter.initialize(fraction, length);
	lossFilter.initialize();
	triggerPoint = (size_t)(0.25 * length);
	deviation = 3e-03;
}

double WaveGuide::getSample()
{
	shiftDelayLines();
	double sample = forwardDelayLine[dataPointer];
	return correctionMultiplier * sample;
}
