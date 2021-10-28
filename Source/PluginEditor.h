/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSR/AdsrEditor.h"
#include "Osc/OscEditor.h"
#include "Filter/FilterEditor.h"

//==============================================================================
/**
*/
class BasicSynthV1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BasicSynthV1AudioProcessorEditor (BasicSynthV1AudioProcessor&);
    ~BasicSynthV1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicSynthV1AudioProcessor& audioProcessor;
    
    AdsrEditor adsr;
    OscEditor oscSelector;
    FilterEditor filterParams;
    AdsrEditor filterAdsr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthV1AudioProcessorEditor)
};
