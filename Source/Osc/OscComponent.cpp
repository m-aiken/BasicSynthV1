/*
  ==============================================================================

    OscComponent.cpp
    Created: 23 Oct 2021 4:40:24pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent (juce::AudioProcessorValueTreeState& apvts)
    : oscSelectorAttachment (apvts, "oscType", oscSelector)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices { "Sine", "Saw", "Square" };
    oscSelector.addItemList (choices, 1);
    addAndMakeVisible (oscSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::lightgrey);
}

void OscComponent::resized()
{
    oscSelector.setBounds (getLocalBounds());
}
