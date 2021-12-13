/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GuitarSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                               private juce::Timer,
                                               private juce::Value::Listener
{
public:
    GuitarSynthesizerAudioProcessorEditor (GuitarSynthesizerAudioProcessor&);
    ~GuitarSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void updateTrackProperties();
    int getControlParameterIndex(Component&) override;
    void hostMIDIControllerIsAvailable(bool) override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GuitarSynthesizerAudioProcessor& getProcessor() const;
    void valueChanged(juce::Value&) override;
    void updateTimecodeDisplay(juce::AudioPlayHead::CurrentPositionInfo pos);
    GuitarSynthesizerAudioProcessor& audioProcessor;
    juce::MidiKeyboardComponent midiKeyboard;

    juce::Label timecodeDisplayLabel,
        gainLabel{ {}, "Volume :" };

    juce::Slider gainSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAttachment;
    juce::Colour backgroundColour;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    juce::Value lastUIWidth, lastUIHeight;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynthesizerAudioProcessorEditor)
};
