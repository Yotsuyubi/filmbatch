/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "NewComponent.h"

//==============================================================================
/**
*/
class FilmbatchAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FilmbatchAudioProcessorEditor (FilmbatchAudioProcessor&);
    ~FilmbatchAudioProcessorEditor();
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilmbatchAudioProcessor& processor;
    NewComponent newComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilmbatchAudioProcessorEditor)
};
