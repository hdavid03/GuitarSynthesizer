/*
  ==============================================================================

    WarpedIIRFilter.h
    Created: 11 Dec 2021 2:23:33am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WarpedIIRFilter  : public juce::Component
{
public:
    WarpedIIRFilter();
    ~WarpedIIRFilter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WarpedIIRFilter)
};
