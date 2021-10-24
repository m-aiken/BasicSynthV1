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
}

void FilterProcessor::processFilter (juce::AudioBuffer<float>& buffer)
{
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

void FilterProcessor::resetFilter ()
{
    filter.reset();
}
