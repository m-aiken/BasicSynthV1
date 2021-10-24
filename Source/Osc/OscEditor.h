/*
  ==============================================================================

    OscEditor.h
    Created: 23 Oct 2021 4:40:24pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscEditor  : public juce::Component
{
public:
    OscEditor (juce::AudioProcessorValueTreeState& apvts);
    ~OscEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelector;
    juce::AudioProcessorValueTreeState::ComboBoxAttachment oscSelectorAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscEditor)
};
