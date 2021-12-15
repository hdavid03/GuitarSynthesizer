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
                                               public juce::Button::Listener,
                                               private juce::Value::Listener
{
public:
    GuitarSynthesizerAudioProcessorEditor (GuitarSynthesizerAudioProcessor&);
    ~GuitarSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button*) override;
    void updateTrackProperties();
    int getControlParameterIndex(Component&) override;
    void hostMIDIControllerIsAvailable(bool) override;
    juce::ToggleButton sustainButton;
    static bool sustainIsActive;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GuitarSynthesizerAudioProcessor& getProcessor() const;
    void valueChanged(juce::Value&) override;
    void updateSustainState(juce::Button*);
    GuitarSynthesizerAudioProcessor& audioProcessor;
    juce::MidiKeyboardComponent midiKeyboard;

    juce::Label guitarTypeLabel{ {}, "Epihone DR-100 Acoustic Guitar" };
    juce::Label gainLabel{ {}, "Volume :" };
    juce::Label sustainLabel{ {}, "Sustain" };

    juce::Slider gainSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAttachment;
    juce::Colour backgroundColour;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    juce::Value lastUIWidth, lastUIHeight;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynthesizerAudioProcessorEditor)
};
