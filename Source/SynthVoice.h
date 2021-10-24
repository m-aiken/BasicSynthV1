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
#include "ADSR/AdsrProcessor.h"
#include "Osc/OscProcessor.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels); // Not override as this fn doesn't come from juce::SynthesiserVoice
    
    void update (const float attack, const float decay, const float sustain, const float release);
    OscProcessor& getOscillator() { return osc; };
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
private:
    AdsrProcessor adsr;
    
    juce::AudioBuffer<float> synthBuffer;
    
    OscProcessor osc;
    
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
};
