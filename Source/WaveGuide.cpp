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
	dataPointer = dataPointer == 0 ? lastArrayIndex : dataPointer - 1;
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

void WaveGuide::initialize(double midiNoteInHertz, double sampleRateInHertz, float velocity)
{
	lossFilter.initialize();
	auto fraction = sampleRateInHertz / midiNoteInHertz - lossFilter.getPhaseDelay(sampleRateInHertz, midiNoteInHertz);
	length = (size_t)fraction / 2;
	double dx = stringLengthInMeter / fraction;
	correctionMultiplier = 2 * tension / dx / sampleRateInHertz;
	lastArrayIndex = length - 1;
	dataPointer = lastArrayIndex;
	fractionalDelayFilter.initialize(fraction, length);
	triggerPoint = (size_t)(0.25 * length);
	deviation = velocity * 3e-03;
}

double WaveGuide::getSample()
{
	shiftDelayLines();
	double sample = forwardDelayLine[dataPointer];
	return correctionMultiplier * sample;
}
