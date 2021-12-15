/*
  ==============================================================================

    WaveGuide.h
    Created: 11 Dec 2021 2:24:36am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <vector>
#include <JuceHeader.h>
#include "LossFilter.h"
#include "FractionalDelayFilter.h"

class WaveGuide
{
public:
	WaveGuide();
	void loadDelayLines();
	void initialize(double, double, float);
	double getSample();

private:
	std::vector<double> forwardDelayLine;
	std::vector<double> backwardDelayLine;
	LossFilter lossFilter;
	FractionalDelayFilter fractionalDelayFilter;
	size_t triggerPoint = 0;
	size_t length = 0;
	size_t dataPointer = 0;
	size_t lastArrayIndex = 0;
	double correctionMultiplier = 0.0;
	const double stringLengthInMeter = 0.6477;
	const double tension = 13.06;
	const int reflection = -1;
	double deviation = 0.0;
	void shiftDelayLines();
};
