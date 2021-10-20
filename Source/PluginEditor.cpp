/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthV1AudioProcessorEditor::BasicSynthV1AudioProcessorEditor (BasicSynthV1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
      attackAttachment (audioProcessor.apvts, "attack", attackSlider),
      decayAttachment (audioProcessor.apvts, "decay", decaySlider),
      sustainAttachment (audioProcessor.apvts, "sustain", sustainSlider),
      releaseAttachment (audioProcessor.apvts, "release", releaseSlider),
      oscSelectorAttachment (audioProcessor.apvts, "oscType", oscSelector)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addADSRSlider (attackSlider, attackLabel, "A");
    addADSRSlider (decaySlider, decayLabel, "D");
    addADSRSlider (sustainSlider, sustainLabel, "S");
    addADSRSlider (releaseSlider, releaseLabel, "R");
    
    setSize (400, 300);
}

BasicSynthV1AudioProcessorEditor::~BasicSynthV1AudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void BasicSynthV1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto container    = getLocalBounds();
    auto topTwenty    = container.removeFromTop (getHeight() * 0.2f);
    auto bottomTwenty = container.removeFromBottom (getHeight() * 0.2f);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid adsrSliders;
    
    adsrSliders.templateRows    = { Track (Fr (1)) };
    adsrSliders.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
    
    adsrSliders.items = { juce::GridItem (attackSlider), juce::GridItem (decaySlider), juce::GridItem (sustainSlider), juce::GridItem (releaseSlider) };
    
    adsrSliders.performLayout (container);
}

void BasicSynthV1AudioProcessorEditor::addADSRSlider (juce::Slider &slider, juce::Label &label, const juce::String &labelText)
{
    addAndMakeVisible (slider);
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    
    addAndMakeVisible (label);
    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.attachToComponent (&slider, false);
}
