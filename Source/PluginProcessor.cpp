/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthV1AudioProcessor::BasicSynthV1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

BasicSynthV1AudioProcessor::~BasicSynthV1AudioProcessor()
{
}

//==============================================================================
const juce::String BasicSynthV1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicSynthV1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthV1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthV1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicSynthV1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicSynthV1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicSynthV1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicSynthV1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicSynthV1AudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicSynthV1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicSynthV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void BasicSynthV1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicSynthV1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void BasicSynthV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // Osc, ADSR, LFO controls...
            auto& attack  = *apvts.getRawParameterValue ("attack");
            auto& decay   = *apvts.getRawParameterValue ("decay");
            auto& sustain = *apvts.getRawParameterValue ("sustain");
            auto& release = *apvts.getRawParameterValue ("release");
            
            auto& oscWave = *apvts.getRawParameterValue ("oscType");
            
            voice->update (attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType (oscWave);
        }
    }
    
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BasicSynthV1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicSynthV1AudioProcessor::createEditor()
{
    return new BasicSynthV1AudioProcessorEditor (*this);
}

//==============================================================================
void BasicSynthV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicSynthV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout BasicSynthV1AudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Choice box for osc type
    juce::StringArray oscTypes { "Sine", "Saw", "Square" };
    layout.add(std::make_unique<juce::AudioParameterChoice> ("oscType", "Oscillator Type", oscTypes, 0));
    
    // ADSR
    // NoramalisableRange args are rangeStart, rangeEnd, interval, defaultValue
    layout.add(std::make_unique<juce::AudioParameterFloat> ("attack",  "Attack",  juce::NormalisableRange<float> (0.1f, 1.0f, 0.01f), 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat> ("decay",   "Decay",   juce::NormalisableRange<float> (0.1f, 1.0f, 0.01f), 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat> ("sustain", "Sustain", juce::NormalisableRange<float> (0.1f, 1.0f, 0.01f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat> ("release", "Release", juce::NormalisableRange<float> (0.1f, 3.0f, 0.01f), 0.4f));
    
    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicSynthV1AudioProcessor();
}
