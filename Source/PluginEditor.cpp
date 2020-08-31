/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SunnBetaLeadEmuAudioProcessorEditor::SunnBetaLeadEmuAudioProcessorEditor (SunnBetaLeadEmuAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    StringArray ampModels = { "Sunn Beta Lead", "Celestion Vintage 30 4X12", "Celestion G12T75 4X12", "Fender Workingmans 12 Combo 1X12", "Marshall VBC810 8X10", "Peavey 5150 4X12", "Sunn 200S 2X15", "Sunn Solarus 2X12", "Vox AX10C1 1X10", "ZILLA-FATBOY-G12K100-III", "GERMAN-112-GOVERNOR", "GERMAN-112-ATYPE-TUBE"};
    ampModelSelector.addItemList(ampModels, 1);
    addAndMakeVisible(&ampModelSelector);
    ampModelSelector.onChange = [this] { ampSelectorCallback();  };
    ampModelSelector.setText("Celestion Vintage 30 4X12", true);
    addAndMakeVisible(convolutionSelector);
    convolutionSelector.onChange = [this] { convolutionSelectorCallback();  };
    convolutionSelector.setText("019c-AT4050-V30-4x12.wav", false);

}

SunnBetaLeadEmuAudioProcessorEditor::~SunnBetaLeadEmuAudioProcessorEditor()
{
}

void SunnBetaLeadEmuAudioProcessorEditor::ampSelectorCallback()
{
    std::string selectedText = ampModelSelector.getText().toStdString();
    currentAmpModel = selectedText;
    std::string dir = "D:/Documents/Development/SunnBetaLeadEmu/Resources/Convolutions/" + selectedText;
    int counter = 0;
    convolutionSelector.clear();
    convolutionSelector.setSelectedItemIndex(0);
    for (auto& conv : std::filesystem::directory_iterator(dir))
    {
        std::string path = conv.path().filename().string();
        size_t pos = path.find_last_of("/");
        path = path.substr(pos + std::string("/").length());
        convolutionSelector.addItem(path, counter + 1);
        ++counter;
    }
    convolutionSelector.setSelectedItemIndex(0, true);
}

void SunnBetaLeadEmuAudioProcessorEditor::convolutionSelectorCallback()
{
    std::string selectedConvolution = convolutionSelector.getText().toStdString();
    if (selectedConvolution != "") {
        std::string combinedPath = "D:/Documents/Development/SunnBetaLeadEmu/Resources/Convolutions/" + currentAmpModel + "/" + selectedConvolution;
        // Now tell the audio thread to load it..
        processor.convolutionChanged(combinedPath);
    }
}

//==============================================================================
void SunnBetaLeadEmuAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::whitesmoke);
    Image sunnLogo = ImageFileFormat::loadFrom(BinaryData::Background_jpg, BinaryData::Background_jpgSize);
    g.drawImage(sunnLogo, Rectangle<float>(getWidth(), getHeight()));
}

void SunnBetaLeadEmuAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    ampModelSelector.setBounds(10, 10, getWidth() / 2, 30);
    convolutionSelector.setBounds(10, 50, getWidth() / 2, 30);
    
}
