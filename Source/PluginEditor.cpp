/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthV1AudioProcessorEditor::BasicSynthV1AudioProcessorEditor (BasicSynthV1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts),
      oscSelectorAttachment (audioProcessor.apvts, "oscType", oscSelector)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (adsr);
    
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
    adsr.setBounds (getLocalBounds());
}
