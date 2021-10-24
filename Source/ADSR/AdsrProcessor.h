/*
  ==============================================================================

    AdsrProcessor.h
    Created: 24 Oct 2021 12:18:43am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrProcessor : public juce::ADSR
{
public:
    void updateAdsr (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};
