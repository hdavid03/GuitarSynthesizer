/*
  ==============================================================================

    GuitarVoice.cpp
    Created: 11 Dec 2021 2:23:06am
    Author:  hdavid03

  ==============================================================================
*/


#include <JuceHeader.h>
#include "GuitarVoice.h"
#include "PluginEditor.h"
#include <iostream>


//==============================================================================
GuitarVoice::GuitarVoice()
{
}

bool GuitarVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<GuitarSound*> (sound) != nullptr;
}

void GuitarVoice::startNote(int midiNoteNumber, float velocity,
    juce::SynthesiserSound* /*sound*/,
    int /*currentPitchWheelPosition*/)
{
    std::cout << "startNote" << std::endl;
    if (midiNoteNumber > 39 && midiNoteNumber < 85)
    {
        std::cout << "startNote:if ok" << std::endl;
        lastSample = 0.0;
        tailOff = true;
        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        sampleRate = getSampleRate();
        stringModel.initialize(cyclesPerSecond, sampleRate, velocity);
        stringModel.loadDelayLines();
    }
}

void GuitarVoice::stopNote(float /*velocity*/, bool /* allowTailOff*/)
{
    if (!GuitarSynthesizerAudioProcessorEditor::sustainIsActive)
    {
        tailOff = false;
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
            auto sampleToOutput = (currentSample - lastSample) * sampleRate;

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
            auto sampleToOutput = (currentSample - lastSample) * sampleRate;
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, sampleToOutput);

            ++startSample;
            lastSample = currentSample;
        }
    }
}
