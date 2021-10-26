/*
  ==============================================================================

    FilterEditor.h
    Created: 27 Oct 2021 12:36:58am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterEditor  : public juce::Component
{
public:
    FilterEditor(juce::AudioProcessorValueTreeState& apvts);
    ~FilterEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector;
    juce::AudioProcessorValueTreeState::ComboBoxAttachment filterTypeAttachment;
    
    juce::Slider cutoffRotary, resonanceRotary;
    juce::Label  cutoffLabel, resonanceLabel;
    juce::AudioProcessorValueTreeState::SliderAttachment cutoffAttachment, resonanceAttachment;
    
    void addCutoffResRotary (juce::Slider &slider, juce::Label &label, const juce::String &labelText);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterEditor)
};
