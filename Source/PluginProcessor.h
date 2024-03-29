/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SpinLockedPos.h"
#include "GuitarSound.h"
#include "GuitarVoice.h"
#include "WarpedIIRFilter.h"

//==============================================================================
/**
*/
class GuitarSynthesizerAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    GuitarSynthesizerAudioProcessor();
    ~GuitarSynthesizerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlock(juce::AudioBuffer<double>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    TrackProperties getTrackProperties() const;
    void updateTrackProperties(const TrackProperties& properties) override;
    void reset() override;

    bool supportsDoublePrecisionProcessing() const override;

    juce::MidiKeyboardState keyboardState;
    SpinLockedPos lastPosInfo;
    juce::AudioProcessorValueTreeState state;

private:
    //==============================================================================
    void initialiseSynth();
    int start = 0;
    int delayPosition = 0;

    juce::Synthesiser synth;
    juce::CriticalSection trackPropertiesLock;
    TrackProperties trackProperties;
    WarpedIIRFilter guitarBodyModel;

    void applyGain(juce::AudioBuffer<float>& buffer, float gainLevel);
    void applyGain(juce::AudioBuffer<double>& buffer, float gainLevel);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynthesizerAudioProcessor)
};
