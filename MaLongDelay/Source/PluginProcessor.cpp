
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MaLongDelayAudioProcessor::MaLongDelayAudioProcessor()
    : parameters(*this, nullptr, "MaLongDelay", {
        std::make_unique<AudioParameterFloat>("DW", "Dry/Wet ratio", 0.0f, 1.0f, DEFAULT_DW),

        std::make_unique<AudioParameterFloat>("DTRight", "Delay time Right (s)", 0.0f, static_cast<float>(MAX_DELAY_TIME), static_cast<float>(DEFAULT_TIME)),
        std::make_unique<AudioParameterFloat>("FBRight", "Feedback Right", 0.0f, 1.0f, DEFAULT_FB),

        std::make_unique<AudioParameterFloat>("DTLeft", "Delay time Left (s)", 0.0f, static_cast<float>(MAX_DELAY_TIME), static_cast<float>(DEFAULT_TIME)),
        std::make_unique<AudioParameterFloat>("FBLeft", "Feedback Left", 0.0f, 1.0f, DEFAULT_FB),
        
        })
{
    parameters.addParameterListener("DW", this);

    parameters.addParameterListener("DTRight", this);
    parameters.addParameterListener("FBRight", this);

    parameters.addParameterListener("DTLeft", this);
    parameters.addParameterListener("FBLeft", this);
    
    
    
}


  
MaLongDelayAudioProcessor::~MaLongDelayAudioProcessor()
{
}

//==============================================================================
void MaLongDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    dryWetter.prepareToPlay(sampleRate, samplesPerBlock);
    delay.prepareToPlay(sampleRate, samplesPerBlock);
   
}




void MaLongDelayAudioProcessor::releaseResources()
{
    
    dryWetter.releaseResources();
    delay.releaseResources();
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MaLongDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void MaLongDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());



    // copy clean buffer
    dryWetter.copyDrySignal(buffer);

    // delay signal
    delay.processBlock(buffer);

    // add delayed signal to clean signal;
    dryWetter.merge(buffer);

    
}

//==============================================================================
bool MaLongDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

const juce::String MaLongDelayAudioProcessor::getName() const
{
    return juce::String();
}

juce::AudioProcessorEditor* MaLongDelayAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

//==============================================================================
void MaLongDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MaLongDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}



void MaLongDelayAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == "DW")
        dryWetter.setDryWetRatio(newValue);

    if (paramID == "DTRight")
        delay.setTimeRight(newValue);

    if (paramID == "FBRight")
        delay.setFeedbackRight(newValue);

    if (paramID == "DTLeft")
        delay.setTimeLeft(newValue);

    if (paramID == "FBLeft")
        delay.setFeedbackLeft(newValue);

    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MaLongDelayAudioProcessor();
}
