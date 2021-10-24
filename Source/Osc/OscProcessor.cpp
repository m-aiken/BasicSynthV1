/*
  ==============================================================================

    OscProcessor.cpp
    Created: 24 Oct 2021 12:18:59am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "OscProcessor.h"

void OscProcessor::prepareOsc (juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare (spec);
    prepare (spec);
}

void OscProcessor::setWaveType (const int choice)
{
    switch (choice)
    {
        case 0: // Sine Wave
            initialise ([](float x) { return std::sin (x); });
            break;
        case 1: // Saw Wave
            initialise ([](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        case 2: // Square Wave
            initialise ([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;
            break;
    }
}

void OscProcessor::setFreq (const int midiNoteNum)
{
    setFrequency (juce::MidiMessage::getMidiNoteInHertz (midiNoteNum) + fmMod);
    lastMidiNote = midiNoteNum;
}

void OscProcessor::processOsc (juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            fmMod = fmOsc.processSample (block.getSample (channel, sample)) * fmDepth;
        }
    }
    
    process (juce::dsp::ProcessContextReplacing<float> (block));
}

void OscProcessor::setFmParams (const float freq, const float depth)
{
    fmOsc.setFrequency (freq);
    fmDepth = depth;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz (lastMidiNote) + fmMod);
}
