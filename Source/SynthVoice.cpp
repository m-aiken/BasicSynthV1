/*
  ==============================================================================

    SynthVoice.cpp
    Created: 17 Oct 2021 2:32:06pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFreq (midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate (sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate       = sampleRate;
    spec.numChannels      = outputChannels;
    
    osc.prepareOsc (spec);
    gain.prepare (spec);
    
    gain.setGainLinear (0.8f);
    
    isPrepared = true;
}

void SynthVoice::update (const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateAdsr (attack, decay, sustain, release);
}

//void SynthVoice::setWaveType (const int choice)
//{
//    switch (choice)
//    {
//        case 0:
//            // Sine Wave
//            osc.initialise ([](float x) { return std::sin (x); });
//            break;
//        case 1:
//            // Saw Wave
//            osc.initialise ([](float x) { return x / juce::MathConstants<float>::pi; });
//            break;
//        case 2:
//            // Square Wave
//            osc.initialise ([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
//            break;
//        default:
//            jassertfalse;
//            break;
//    }
//}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    
    if (!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.processOsc (audioBlock);
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (!adsr.isActive())
            clearCurrentNote();
    }
}
