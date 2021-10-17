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
    setSize (400, 300);
}

BasicSynthV1AudioProcessorEditor::~BasicSynthV1AudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BasicSynthV1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
