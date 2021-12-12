/*
  ==============================================================================

    WaveGuide.h
    Created: 11 Dec 2021 2:24:36am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveGuide  : public juce::Component
{
public:
    WaveGuide();
    ~WaveGuide() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveGuide)
};
