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
    void setFmParams (const float freq, const float depth);
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); }};
    float fmMod { 0.0f };
    float fmDepth { 1.0f };
    int lastMidiNote { 0 };
};
