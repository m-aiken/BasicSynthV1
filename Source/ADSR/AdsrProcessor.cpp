/*
  ==============================================================================

    AdsrProcessor.cpp
    Created: 24 Oct 2021 12:18:43am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "AdsrProcessor.h"

void AdsrProcessor::updateAdsr (const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack  = attack;
    adsrParams.decay   = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters (adsrParams);
}
