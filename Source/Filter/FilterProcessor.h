/*
  ==============================================================================

    FilterProcessor.h
    Created: 24 Oct 2021 11:00:24pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterProcessor
{
public:
    void prepareFilter (double sampleRate, int samplesPerBlock, int outputChannels);
    void processFilter (juce::AudioBuffer<float>& buffer);
    void updateFilter (const int filterType, const float frequency, const float resonance);
    void resetFilter ();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
};
