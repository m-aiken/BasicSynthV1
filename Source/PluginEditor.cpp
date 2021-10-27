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
      adsr (audioProcessor.apvts),
      oscSelector (audioProcessor.apvts),
      filterParams (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (adsr);
    addAndMakeVisible (oscSelector);
    addAndMakeVisible (filterParams);
    setSize (600, 400);
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
    auto container = getLocalBounds().reduced (10);
    
    //auto bottom = container.removeFromBottom (getHeight() * 0.5f);
    
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    
    juce::Grid grid;
    
    grid.templateColumns = { Track (Fr (1)), Track (Fr (1)) };
    grid.templateRows    = { Track (Fr (1)), Track (Fr (1)) };
    
    grid.items = {
        juce::GridItem (oscSelector),  juce::GridItem (adsr),
        juce::GridItem (filterParams), juce::GridItem ()
    };
    
    grid.performLayout (container);
}
