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
class SpinLockedPos
{
public:
    SpinLockedPos();

    // Wait-free, but setting new info may fail if the main thread is currently
    // calling `get`. This is unlikely to matter in practice because
    // we'll be calling `set` much more frequently than `get`.
    void set(const juce::AudioPlayHead::CurrentPositionInfo& newInfo);
    juce::AudioPlayHead::CurrentPositionInfo get() const noexcept;

private:
    juce::SpinLock mutex;
    juce::AudioPlayHead::CurrentPositionInfo info;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpinLockedPos)
};
