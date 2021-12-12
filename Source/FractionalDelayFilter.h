/*
  ==============================================================================

    FractionalDelayFilter.h
    Created: 11 Dec 2021 2:22:09am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FractionalDelayFilter  : public juce::Component
{
public:
    FractionalDelayFilter();
    ~FractionalDelayFilter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FractionalDelayFilter)
};
