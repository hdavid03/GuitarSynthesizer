/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GuitarSynthesizerAudioProcessor::GuitarSynthesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    state(*this, nullptr, "state",
        { std::make_unique<juce::AudioParameterFloat>("gain",  "Gain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.9f) })
#endif
{
    state.state.addChild({ "uiState", { { "width",  720 }, { "height", 240 } }, {} }, -1, nullptr);
    guitarBodyModel.initialize();
    initialiseSynth();
}

GuitarSynthesizerAudioProcessor::~GuitarSynthesizerAudioProcessor()
{
}

//==============================================================================
const juce::String GuitarSynthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GuitarSynthesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GuitarSynthesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GuitarSynthesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GuitarSynthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GuitarSynthesizerAudioProcessor::getNumPrograms()
{
    return 0;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GuitarSynthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GuitarSynthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GuitarSynthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void GuitarSynthesizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GuitarSynthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    setProcessingPrecision(juce::AudioProcessor::ProcessingPrecision::doublePrecision);
    synth.setCurrentPlaybackSampleRate(sampleRate);
    keyboardState.reset();
    reset();
}

void GuitarSynthesizerAudioProcessor::releaseResources()
{
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GuitarSynthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GuitarSynthesizerAudioProcessor::processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert(isUsingDoublePrecision());
    auto gainParamValue = state.getParameter("gain")->getValue();
    auto numSamples = buffer.getNumSamples();
    auto numOfOutputChannels = getTotalNumOutputChannels();

    for (auto i = getTotalNumInputChannels(); i < numOfOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

    guitarBodyModel.filterBuffer(buffer);
    // Apply our gain change to the outgoing data..
    gainParamValue *= 1e-04;
    //gainParamValue *= 1e+02;
    applyGain(buffer, gainParamValue);
    updateCurrentTimeInfoFromHost();
}

void GuitarSynthesizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert(!isUsingDoublePrecision());
    auto gainParamValue = state.getParameter("gain")->getValue();
    auto numSamples = buffer.getNumSamples();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, numSamples);

    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    applyGain(buffer, gainParamValue);

    updateCurrentTimeInfoFromHost();
}

//==============================================================================
bool GuitarSynthesizerAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* GuitarSynthesizerAudioProcessor::createEditor()
{
    return new GuitarSynthesizerAudioProcessorEditor (*this);
}

//==============================================================================
void GuitarSynthesizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void GuitarSynthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        state.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor::TrackProperties GuitarSynthesizerAudioProcessor::getTrackProperties() const
{
    const juce::ScopedLock sl(trackPropertiesLock);
    return trackProperties;
}

void GuitarSynthesizerAudioProcessor::reset()
{
    guitarBodyModel.initialize();
}

bool GuitarSynthesizerAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return true;
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GuitarSynthesizerAudioProcessor();
}

void GuitarSynthesizerAudioProcessor::updateTrackProperties(const TrackProperties& properties)
{
    {
        const juce::ScopedLock sl(trackPropertiesLock);
        trackProperties = properties;
    }

    juce::MessageManager::callAsync([this]
        {
            if (auto* editor = dynamic_cast<GuitarSynthesizerAudioProcessorEditor*> (getActiveEditor()))
                editor->updateTrackProperties();
        });
}

void GuitarSynthesizerAudioProcessor::applyGain(juce::AudioBuffer<float>& buffer, float gainLevel)
{
    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        buffer.applyGain(channel, 0, buffer.getNumSamples(), gainLevel);
}

void GuitarSynthesizerAudioProcessor::applyGain(juce::AudioBuffer<double>& buffer, float gainLevel)
{
    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        buffer.applyGain(channel, 0, buffer.getNumSamples(), gainLevel);
}

void GuitarSynthesizerAudioProcessor::updateCurrentTimeInfoFromHost()
{
    const auto newInfo = [&]
    {
        if (auto* ph = getPlayHead())
        {
            juce::AudioPlayHead::CurrentPositionInfo result;

            if (ph->getCurrentPosition(result))
                return result;
        }
        juce::AudioPlayHead::CurrentPositionInfo result;
        result.resetToDefault();
        return result;
    }();

    lastPosInfo.set(newInfo);
}


void GuitarSynthesizerAudioProcessor::initialiseSynth()
{
    auto numVoices = 6;
    for (auto i = 0; i < numVoices; ++i)
        synth.addVoice(new GuitarVoice());
    synth.addSound(new GuitarSound());
}
