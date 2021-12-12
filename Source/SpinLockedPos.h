/*
  ==============================================================================

    SpinLockedPos.h
    Created: 11 Dec 2021 2:24:11am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpinLockedPos  : public juce::Component
{
public:
    SpinLockedPos();
    ~SpinLockedPos() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpinLockedPos)
};
