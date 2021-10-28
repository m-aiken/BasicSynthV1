/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 24 Oct 2021 11:00:24pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "FilterProcessor.h"

void FilterProcessor::prepareFilter (double sampleRate, int samplesPerBlock, int outputChannels)
{
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate       = sampleRate;
    spec.numChannels      = outputChannels;
    
    filter.prepare (spec);
    
    isPrepared = true;
}

void FilterProcessor::processFilter (juce::AudioBuffer<float>& buffer)
{
    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> block { buffer };
    
    filter.process (juce::dsp::ProcessContextReplacing<float> { block });
}

void FilterProcessor::updateFilter (const int filterType, const float frequency, const float resonance)
{
    switch (filterType) {
        case 0:
            filter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType (juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType (juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    
    filter.setCutoffFrequency (frequency);
    filter.setResonance (resonance);
}

void FilterProcessor::updateEnvelope (const float attack, const float decay, const float sustain, const float release)
{
    filterAdsr.updateAdsr (attack, decay, sustain, release);
}

void FilterProcessor::resetFilter ()
{
    filter.reset();
}
