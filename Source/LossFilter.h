/*
  ==============================================================================

    LossFilter.h
    Created: 11 Dec 2021 2:22:27am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

class LossFilter
{
public:
    LossFilter();
    double filterSample(double);
    void initialize();
    double getPhaseDelay(double, double);

private:
    const double g = 0.99572;
    const double a = -0.2414;
    double y = 0.0;
};
