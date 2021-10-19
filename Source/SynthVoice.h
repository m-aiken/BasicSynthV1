/*
  ==============================================================================

    SynthVoice.h
    Created: 17 Oct 2021 2:32:06pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels); // Not override as this fn doesn't come from juce::SynthesiserVoice
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void updateAdsr (const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::AudioBuffer<float> synthBuffer;
    
    juce::dsp::Oscillator<float> osc { [](float x) { return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
    
    // [](float x) { return std::sin (x); }                 // Sine Wave
    // [](float x) { return x / juce::MathConstants<float>::pi; } // Saw Wave
    // [](float x) { return x < 0.0f ? -1.0f : 1.0f; }      // Square Wave
};
