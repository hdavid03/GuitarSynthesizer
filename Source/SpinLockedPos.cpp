/*
  ==============================================================================

    SpinLockedPos.cpp
    Created: 11 Dec 2021 2:24:11am
    Author:  hdavid03

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpinLockedPos.h"

//==============================================================================
SpinLockedPos::SpinLockedPos() { info.resetToDefault(); }

// Wait-free, but setting new info may fail if the main thread is currently
// calling `get`. This is unlikely to matter in practice because
// we'll be calling `set` much more frequently than `get`.
void SpinLockedPos::set(const juce::AudioPlayHead::CurrentPositionInfo& newInfo)
{
    const juce::SpinLock::ScopedTryLockType lock(mutex);

    if (lock.isLocked())
        info = newInfo;
}


juce::AudioPlayHead::CurrentPositionInfo SpinLockedPos::get() const noexcept
{
    const juce::SpinLock::ScopedLockType lock(mutex);
    return info;
}
