/*
  ==============================================================================

    AdsrEditor.cpp
    Created: 23 Oct 2021 2:07:46pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "AdsrEditor.h"

//==============================================================================
AdsrEditor::AdsrEditor (juce::AudioProcessorValueTreeState& apvts)
    : attackAttachment  (apvts, "attack", attackSlider),
      decayAttachment   (apvts, "decay", decaySlider),
      sustainAttachment (apvts, "sustain", sustainSlider),
      releaseAttachment (apvts, "release", releaseSlider)
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
}

void AdsrEditor::resized()
{
    auto container    = getLocalBounds();
    auto topTwenty    = container.removeFromTop (getHeight() * 0.2f);
    auto bottomTwenty = container.removeFromBottom (getHeight() * 0.2f);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid adsrSliders;
    
    adsrSliders.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    adsrSliders.templateRows    = { Track (Fr (1)) };
    
    adsrSliders.items = { juce::GridItem (attackSlider), juce::GridItem (decaySlider), juce::GridItem (sustainSlider), juce::GridItem (releaseSlider) };
    
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
    label.attachToComponent (&slider, false);
}
