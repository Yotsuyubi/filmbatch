/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilmbatchAudioProcessorEditor::FilmbatchAudioProcessorEditor (FilmbatchAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(newComponent);
    newComponent.setSize(this->getWidth(), this->getHeight());
}

FilmbatchAudioProcessorEditor::~FilmbatchAudioProcessorEditor()
{
}
