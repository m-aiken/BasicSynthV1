/*
  ==============================================================================

    AdsrEditor.cpp
    Created: 23 Oct 2021 2:07:46pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "AdsrEditor.h"

//==============================================================================
AdsrEditor::AdsrEditor (juce::AudioProcessorValueTreeState& apvts, int type)
    : attackOptions ("attack", "filterAttack"),
      decayOptions ("decay", "filterDecay"),
      sustainOptions ("sustain", "filterSustain"),
      releaseOptions ("release", "filterRelease"),
      attackAttachment  (apvts, attackOptions[type], attackSlider),
      decayAttachment   (apvts, decayOptions[type], decaySlider),
      sustainAttachment (apvts, sustainOptions[type], sustainSlider),
      releaseAttachment (apvts, releaseOptions[type], releaseSlider)
{
    addADSRSlider (attackSlider, attackLabel, "A");
    addADSRSlider (decaySlider, decayLabel, "D");
    addADSRSlider (sustainSlider, sustainLabel, "S");
    addADSRSlider (releaseSlider, releaseLabel, "R");
}

AdsrEditor::~AdsrEditor()
{
}

void AdsrEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 5.0f, 2.0f);
}

void AdsrEditor::resized()
{
    auto container = getLocalBounds().reduced (10);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid adsrSliders;
    
    adsrSliders.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    adsrSliders.templateRows    = { Track (Fr (1)), Track (Fr (5)) };
    
    adsrSliders.items = {
        juce::GridItem (attackLabel),  juce::GridItem (decayLabel),  juce::GridItem (sustainLabel),  juce::GridItem (releaseLabel),
        juce::GridItem (attackSlider), juce::GridItem (decaySlider), juce::GridItem (sustainSlider), juce::GridItem (releaseSlider)
    };
    
    adsrSliders.performLayout (container);
}

void AdsrEditor::addADSRSlider (juce::Slider &slider, juce::Label &label, const juce::String &labelText)
{
    addAndMakeVisible (slider);
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    
    addAndMakeVisible (label);
    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    //label.attachToComponent (&slider, false);
}
