/*
  ==============================================================================

    FilterEditor.cpp
    Created: 27 Oct 2021 12:36:58am
    Author:  Matt Aiken

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterEditor.h"

//==============================================================================
FilterEditor::FilterEditor(juce::AudioProcessorValueTreeState& apvts)
    : filterTypeAttachment (apvts, "filterType", filterTypeSelector),
      cutoffAttachment (apvts, "cutoff", cutoffRotary),
      resonanceAttachment (apvts, "resonance", resonanceRotary)
{
    juce::StringArray filterOptions { "Lowpass", "Bandpass", "Highpass" };
    filterTypeSelector.addItemList (filterOptions, 1);
    filterTypeSelector.setSelectedId (1);
    addAndMakeVisible (filterTypeSelector);
    
    addCutoffResRotary (cutoffRotary, cutoffLabel, "Cutoff");
    addCutoffResRotary (resonanceRotary, resonanceLabel, "Resonance");
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 5.0f, 2.0f);
}

void FilterEditor::resized()
{
    auto container = getLocalBounds().reduced (10);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid filterParams;
    /*
    filterParams.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    filterParams.templateRows    = { Track (Fr (1)) };
    
    filterParams.items = { juce::GridItem (filterTypeSelector), juce::GridItem (cutoffRotary), juce::GridItem (resonanceRotary) };
    */
    filterParams.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    filterParams.templateRows = {
        Track (Fr (1)),
        Track (Fr (4))
    };
    
    filterParams.items = { juce::GridItem (filterTypeSelector), juce::GridItem (cutoffLabel),  juce::GridItem (resonanceLabel),
                           juce::GridItem (),                   juce::GridItem (cutoffRotary), juce::GridItem (resonanceRotary) };
    
    filterParams.performLayout (container);

}

void FilterEditor::addCutoffResRotary (juce::Slider &slider, juce::Label &label, const juce::String &labelText)
{
    addAndMakeVisible (slider);
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    
    addAndMakeVisible (label);
    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    //label.attachToComponent (&slider, false);
}
