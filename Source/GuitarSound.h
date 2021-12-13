/*
  ==============================================================================

    GuitarSound.h
    Created: 11 Dec 2021 2:22:49am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GuitarSound  : public juce::SynthesiserSound
{
public:
    GuitarSound();

    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel(int /*midiChannel*/) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSound)
};
