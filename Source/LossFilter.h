/*
  ==============================================================================

    LossFilter.h
    Created: 11 Dec 2021 2:22:27am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LossFilter  : public juce::Component
{
public:
    LossFilter();
    ~LossFilter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LossFilter)
};
