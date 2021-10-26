/*
  ==============================================================================

    FilterEditor.h
    Created: 27 Oct 2021 12:36:58am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FIlterEditor  : public juce::Component
{
public:
    FIlterEditor();
    ~FIlterEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FIlterEditor)
};
