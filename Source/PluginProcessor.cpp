/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SunnBetaLeadEmuAudioProcessor::SunnBetaLeadEmuAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                       )
{
}

SunnBetaLeadEmuAudioProcessor::~SunnBetaLeadEmuAudioProcessor()
{
}

//==============================================================================
const String SunnBetaLeadEmuAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SunnBetaLeadEmuAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SunnBetaLeadEmuAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SunnBetaLeadEmuAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SunnBetaLeadEmuAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SunnBetaLeadEmuAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SunnBetaLeadEmuAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SunnBetaLeadEmuAudioProcessor::setCurrentProgram (int index)
{
}

const String SunnBetaLeadEmuAudioProcessor::getProgramName (int index)
{
    return {};
}

void SunnBetaLeadEmuAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SunnBetaLeadEmuAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;
    spb = samplesPerBlock;
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    convolution1.prepare(spec);
    convolution1.loadImpulseResponse(File("D:\\Documents\\Development\\SunnBetaLeadEmu\\Resources\\Convolutions\\Celestion Vintage 30 4X12\\019c-AT4050-V30-4x12.wav"), dsp::Convolution::Stereo::no, dsp::Convolution::Trim::no, 0);
}

void SunnBetaLeadEmuAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
void SunnBetaLeadEmuAudioProcessor::convolutionChanged(std::string conv)
{
    dsp::ProcessSpec spec;
    spec.sampleRate = sr;
    spec.maximumBlockSize = spb;
    spec.numChannels = getTotalNumOutputChannels();
    if (prevConvIndex == 0)
    {
        convolution2.prepare(spec);
        convolution2.loadImpulseResponse(File(conv), dsp::Convolution::Stereo::no, dsp::Convolution::Trim::no, 0);
        prevConvIndex = 1;
        convolution1.reset();
    }
    else
    {
        convolution1.prepare(spec);
        convolution1.loadImpulseResponse(File(conv), dsp::Convolution::Stereo::no, dsp::Convolution::Trim::no, 0);
        prevConvIndex = 0;
        convolution2.reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SunnBetaLeadEmuAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SunnBetaLeadEmuAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    buffer.copyFrom(1, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    dsp::AudioBlock<float> dspBlock{ buffer };
    dsp::ProcessContextReplacing<float> context{ dspBlock };
    if (prevConvIndex == 0) {
        convolution1.process(context);
    }
    else {
        convolution2.process(context);
    }
}

//==============================================================================
bool SunnBetaLeadEmuAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SunnBetaLeadEmuAudioProcessor::createEditor()
{
    return new SunnBetaLeadEmuAudioProcessorEditor (*this);
}

//==============================================================================
void SunnBetaLeadEmuAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SunnBetaLeadEmuAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SunnBetaLeadEmuAudioProcessor();
}
