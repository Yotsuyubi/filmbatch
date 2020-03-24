/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilmbatchAudioProcessor::FilmbatchAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
//    addParameter (phase = new AudioParameterFloat ("phaseSlider", // parameter ID
//                                                  "phase", // parameter name
//                                                  0.0f,   // minimum value
//                                                  1.0f,   // maximum value
//                                                  0.5f)); // default value
    addParameter (dry = new AudioParameterFloat ("drySlider", // parameter ID
                                                  "dry", // parameter name
                                                  0.0f,   // minimum value
                                                  5.0f,   // maximum value
                                                  1.0f)); // default value
    addParameter (wet = new AudioParameterFloat ("wetSlider", // parameter ID
                                                  "wet", // parameter name
                                                  0.0f,   // minimum value
                                                  5.0f,   // maximum value
                                                  1.0f)); // default value
    addParameter (bitDepth = new AudioParameterInt ("bitDepthSlider", // parameter ID
                                                  "bitDepth", // parameter name
                                                  1,   // minimum value
                                                  24,   // maximum value
                                                  24)); // default value
    addParameter (bitRate = new AudioParameterInt ("bitRateSlider", // parameter ID
                                                  "downsample", // parameter name
                                                  1,   // minimum value
                                                  40,   // maximum value
                                                  1)); // default value
    
}

FilmbatchAudioProcessor::~FilmbatchAudioProcessor()
{
}

//==============================================================================
const String FilmbatchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilmbatchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilmbatchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilmbatchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FilmbatchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilmbatchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilmbatchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilmbatchAudioProcessor::setCurrentProgram (int index)
{
}

const String FilmbatchAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilmbatchAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilmbatchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FilmbatchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilmbatchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void shift(float* channelData, int channelDataLength, int shift)
{
    float shifted[channelDataLength];
    for (auto i = 0; i < channelDataLength; ++i)
    {
        if (i+shift < channelDataLength)
            shifted[i] = channelData[i+shift];
        else
            shifted[i] = channelData[i-shift];
    }
    channelData = shifted;
}

#define ROUND(f) ((float)((f > 0.0) ? floor(f + 0.5) : ceil(f - 0.5)))
void FilmbatchAudioProcessor::bitCrusher(int bitDepth, int bitRate, int samplingRate, float *buffer, int bufferLength)
{
    int max = static_cast<int>(pow(2.0, static_cast<double>(bitDepth))) - 1;
    int step = static_cast<int>(samplingRate/bitRate);
    
    int i = 0;
    while (i < bufferLength)
    {
        float firstSample = ROUND((buffer[i] + 1.0) * max) / max - 1.0;
        
        for (auto j = 0; j < step && i < bufferLength; j++)
        {
            buffer[i] = firstSample;
            i++;
        }
    }
}

void FilmbatchAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        const int bufferLength = buffer.getNumSamples();
        int samplingRate = getSampleRate();
        
        float wetV = wet->get();
        float dryV = dry->get();
        int bitDepthV = bitDepth->get();
        int bitRateV = static_cast<int>(samplingRate / bitRate->get());
        
        float* modData = channelData;
        int idx[bufferLength];
        for (auto i = 0; i < bufferLength; ++i)
            idx[i] = static_cast<int>((modData[i]+1.0)/2.0*static_cast<float>(bufferLength-1));
        float shape[bufferLength];
        for (auto i = 0; i < bufferLength; ++i)
            shape[i] = modData[idx[i]];
        
        float waveShaped[bufferLength];
        for (auto i = 0; i < bufferLength; ++i)
            waveShaped[i] = channelData[i]*shape[i];
        
        bitCrusher(bitDepthV, bitRateV, samplingRate, waveShaped, bufferLength);
        
        for (auto sample = 0; sample < bufferLength; ++sample)
            channelData[sample] = dryV*channelData[sample] + wetV*waveShaped[sample];
        // ..do something to the data...
    }
}

//==============================================================================
bool FilmbatchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilmbatchAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void FilmbatchAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilmbatchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilmbatchAudioProcessor();
}
