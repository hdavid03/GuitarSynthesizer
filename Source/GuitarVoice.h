/*
  ==============================================================================

    GuitarVoice.h
    Created: 11 Dec 2021 2:23:05am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GuitarVoice  : public juce::Component
{
public:
    GuitarVoice();
    ~GuitarVoice() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarVoice)
};
