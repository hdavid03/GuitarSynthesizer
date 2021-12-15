/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
bool GuitarSynthesizerAudioProcessorEditor::sustainIsActive = false;

GuitarSynthesizerAudioProcessorEditor::GuitarSynthesizerAudioProcessorEditor (GuitarSynthesizerAudioProcessor& p)
: AudioProcessorEditor(p),
  audioProcessor(p),
  midiKeyboard(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
  gainAttachment(p.state, "gain", gainSlider)
{
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setColour(juce::Slider::backgroundColourId, juce::Colour::fromRGB(20,121,5));

    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setFont(juce::Font(16.0f));

    midiKeyboard.setAvailableRange(40, 84);
    addAndMakeVisible(midiKeyboard);

    addAndMakeVisible(guitarTypeLabel);
    guitarTypeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 22.0f, juce::Font::plain));

    sustainButton.setAccessible(true);
    sustainButton.setColour(juce::ToggleButton::tickColourId, juce::Colours::aqua);
    addAndMakeVisible(sustainButton);
    sustainButton.onClick = [this]()
    {
        updateSustainState(&sustainButton);
    };
    sustainLabel.attachToComponent(&sustainButton, true);

    setSize(450, 240);

    updateTrackProperties();
}

GuitarSynthesizerAudioProcessorEditor::~GuitarSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void GuitarSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(backgroundColour);
    g.fillAll();
}

void GuitarSynthesizerAudioProcessorEditor::resized()
{
    auto r = getLocalBounds().reduced(8);

    guitarTypeLabel.setBounds(r.removeFromTop(26));
    midiKeyboard.setBounds(r.removeFromBottom(70));
    sustainButton.setBounds(r.removeFromRight(40));

    r.removeFromTop(20);
    auto sliderArea = r.removeFromTop(60);
    gainSlider.setBounds(sliderArea.removeFromLeft(juce::jmin(180, sliderArea.getWidth() / 2)));
}

void GuitarSynthesizerAudioProcessorEditor::buttonClicked(juce::Button* button)
{

}

void GuitarSynthesizerAudioProcessorEditor::updateTrackProperties()
{
        auto trackColour = getProcessor().getTrackProperties().colour;
        auto& lf = getLookAndFeel();

        backgroundColour = (trackColour == juce::Colour() ? lf.findColour(juce::ResizableWindow::backgroundColourId)
            : trackColour.withAlpha(1.0f).withBrightness(0.266f));
        repaint();
}

int GuitarSynthesizerAudioProcessorEditor::getControlParameterIndex(Component& control)
{
    if (&control == &gainSlider)
        return 0;

    return -1;
}

void GuitarSynthesizerAudioProcessorEditor::hostMIDIControllerIsAvailable(bool controllerIsAvailable)
{
    midiKeyboard.setVisible(!controllerIsAvailable);
}


GuitarSynthesizerAudioProcessor& GuitarSynthesizerAudioProcessorEditor::getProcessor() const
{
    return audioProcessor;
}

void GuitarSynthesizerAudioProcessorEditor::valueChanged(juce::Value&)
{
    setSize(lastUIWidth.getValue(), lastUIHeight.getValue());
}

void GuitarSynthesizerAudioProcessorEditor::updateSustainState(juce::Button* button)
{
    sustainIsActive = button->getToggleState();
    if (!sustainIsActive)
    {

    }
}
