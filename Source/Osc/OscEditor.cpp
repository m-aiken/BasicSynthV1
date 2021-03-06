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
    : oscSelectorAttachment (apvts, "oscType", oscSelector),
      fmFreqAttachment (apvts, "fmFreq", fmFreqSlider),
      fmDepthAttachment (apvts, "fmDepth", fmDepthSlider)
{
    juce::StringArray choices { "Sine", "Saw", "Square" };
    oscSelector.addItemList (choices, 1);
    oscSelector.setSelectedId (1);
    addAndMakeVisible (oscSelector);
    
    addFMRotary (fmFreqSlider, fmFreqLabel, "FM Frequency");
    addFMRotary (fmDepthSlider, fmDepthLabel, "FM Depth");
}

OscEditor::~OscEditor()
{
}

void OscEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 5.0f, 2.0f);
}

void OscEditor::resized()
{
    auto container = getLocalBounds().reduced (10);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid params;
    
    params.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    params.templateRows = {
        Track (Fr (1)),
        Track (Fr (4))
    };
    
    params.items = { juce::GridItem (oscSelector), juce::GridItem (fmFreqLabel),  juce::GridItem (fmDepthLabel),
                     juce::GridItem (),            juce::GridItem (fmFreqSlider), juce::GridItem (fmDepthSlider) };
    
    params.performLayout (container);
}

void OscEditor::addFMRotary (juce::Slider &slider, juce::Label &label, const juce::String &labelText)
{
    addAndMakeVisible (slider);
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    
    addAndMakeVisible (label);
    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
}
