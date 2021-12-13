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

private:
    const double g = 0.99688;
    const double a = -0.212;
    double y = 0.0;
};
