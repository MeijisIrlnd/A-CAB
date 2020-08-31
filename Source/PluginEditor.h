/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <filesystem>

//==============================================================================
/**
*/
class SunnBetaLeadEmuAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SunnBetaLeadEmuAudioProcessorEditor (SunnBetaLeadEmuAudioProcessor&);
    ~SunnBetaLeadEmuAudioProcessorEditor();
    void ampSelectorCallback();
    void convolutionSelectorCallback();
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SunnBetaLeadEmuAudioProcessor& processor;
    ComboBox ampModelSelector;
    ComboBox convolutionSelector;
    std::string currentAmpModel = "Celestion Vintage 30 4X12";
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunnBetaLeadEmuAudioProcessorEditor)
};
