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
    BasicSynthV1AudioProcessor& audioProcessor;
    
    AdsrEditor adsr;
    OscEditor oscSelector;
    FilterEditor filterParams;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthV1AudioProcessorEditor)
};
