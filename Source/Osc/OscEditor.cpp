/*
  ==============================================================================

    OscEditor.cpp
    Created: 23 Oct 2021 4:40:24pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "OscEditor.h"

//==============================================================================
OscEditor::OscEditor (juce::AudioProcessorValueTreeState& apvts)
    : oscSelectorAttachment (apvts, "oscType", oscSelector)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices { "Sine", "Saw", "Square" };
    oscSelector.addItemList (choices, 1);
    addAndMakeVisible (oscSelector);
}

OscEditor::~OscEditor()
{
}

void OscEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void OscEditor::resized()
{
    oscSelector.setBounds (5, 5, 90, 20);
}
