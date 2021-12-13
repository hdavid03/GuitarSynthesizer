/*
  ==============================================================================

    GuitarVoice.cpp
    Created: 11 Dec 2021 2:23:06am
    Author:  hdavid03

  ==============================================================================
*/


#include <JuceHeader.h>
#include "GuitarVoice.h"


//==============================================================================
GuitarVoice::GuitarVoice()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

bool GuitarVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<GuitarSound*> (sound) != nullptr;
}

void GuitarVoice::startNote(int midiNoteNumber, float velocity,
    juce::SynthesiserSound* /*sound*/,
    int /*currentPitchWheelPosition*/)
{
    if (midiNoteNumber > 39 && midiNoteNumber < 85)
    {
        lastSample = 0.0;
        tailOff = true;
        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        sampleRate = getSampleRate();
        stringModel.initialize(cyclesPerSecond, sampleRate);
        stringModel.loadDelayLines();
    }
}

void GuitarVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.

        // we only need to begin a tail-off if it's not already doing so - the
                             // stopNote method could be called more than once.
        tailOff = false;
        // we're being told to stop playing immediately, so reset everything..

        clearCurrentNote();
    }
}

void GuitarVoice::pitchWheelMoved(int /*newValue*/)
{
    // not implemented for the purposes of this demo!
}

void GuitarVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/)
{
    // not implemented for the purposes of this demo!
}

void GuitarVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
        if (tailOff)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = stringModel.getSample();
                //auto sampleToOutput = (currentSample - lastSample) * sampleRate;
                auto sampleToOutput = currentSample;
                // sampleToOutput = warpedFilter.filterSample(sampleToOutput);
                // sampleToOutput *= 3.662109375e-04;
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, sampleToOutput);

                ++startSample;
                lastSample = currentSample;
            }
        }
}

void GuitarVoice::renderNextBlock(juce::AudioBuffer<double>& outputBuffer, int startSample, int numSamples)
{
    if (tailOff)
    {
        while (--numSamples >= 0)
        {
            auto currentSample = stringModel.getSample();
            auto sampleToOutput = (currentSample - lastSample) * sampleRate * 0.1;
            // sampleToOutput = warpedFilter.filterSample(sampleToOutput);
            // sampleToOutput *= 0.0009765625;
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, sampleToOutput);

            ++startSample;
            lastSample = currentSample;
        }
    }
}
