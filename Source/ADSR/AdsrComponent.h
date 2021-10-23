/*
  ==============================================================================

    AdsrComponent.h
    Created: 23 Oct 2021 2:07:46pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent (juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label  attackLabel,  decayLabel,  sustainLabel,  releaseLabel;
    juce::AudioProcessorValueTreeState::SliderAttachment attackAttachment, decayAttachment, sustainAttachment, releaseAttachment;
    
    void addADSRSlider (juce::Slider &slider, juce::Label &label, const juce::String &labelText);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
