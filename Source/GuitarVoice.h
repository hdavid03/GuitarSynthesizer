/*
  ==============================================================================

    GuitarVoice.h
    Created: 11 Dec 2021 2:23:05am
    Author:  hdavid03

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuitarSound.h"
#include "WaveGuide.h"
#include "WarpedIIRFilter.h"

//==============================================================================
/*
*/
class GuitarVoice : public juce::SynthesiserVoice
{
public:
    GuitarVoice();
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void renderNextBlock(juce::AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override;

    using juce::SynthesiserVoice::renderNextBlock;

private:
    bool tailOff = false;
    double sampleRate = 0.0;
    double lastSample = 0.0;
    WaveGuide stringModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarVoice)
};
