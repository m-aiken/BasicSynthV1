/*
  ==============================================================================

    OscProcessor.h
    Created: 24 Oct 2021 12:18:59am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscProcessor : public juce::dsp::Oscillator<float>
{
public:
    void prepareOsc (juce::dsp::ProcessSpec& spec);
    void setWaveType (const int choice);
    void setFreq (const int midiNoteNum);
    void processOsc (juce::dsp::AudioBlock<float>& block);
private:
    
};
