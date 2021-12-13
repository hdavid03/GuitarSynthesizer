/*
  ==============================================================================

    GuitarSound.cpp
    Created: 11 Dec 2021 2:22:49am
    Author:  hdavid03

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GuitarSound.h"

//==============================================================================
GuitarSound::GuitarSound()
{

}

bool GuitarSound::appliesToNote(int /*midiNoteNumber*/) { return true; }
bool GuitarSound::appliesToChannel(int /*midiChannel*/) { return true; }

