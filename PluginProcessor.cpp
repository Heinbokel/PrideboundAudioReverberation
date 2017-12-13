/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PrideboundReverberationAudioProcessor::PrideboundReverberationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        treeState(*this,nullptr) //initialize treeState for automation parameters

#endif
{
    NormalisableRange<float> reverbSliderRange(0.0f,100.0f,0.01f); //range for reverb slider automation
    NormalisableRange<float> buttonRange(0.0f,1.0f); //range for button automation.
    NormalisableRange<float> roomScalerange(0.0f,3.0f,1.0f); //range for button automation.
    NormalisableRange<float> hfCutRange(0.0f,20000.0f,1.0f); //range for button automation.
    NormalisableRange<float> gainRange(-48.0f,6.0f,0.01f); //range for button automation.
    
    //add listeners to each parameter so that changes are registered with listener object.
    treeState.addParameterListener("Dry/Wet Level", treeStateListener);
    treeState.addParameterListener("Room Size", treeStateListener);
    treeState.addParameterListener("Gain", treeStateListener);
    treeState.addParameterListener("Damping Level", treeStateListener);
    treeState.addParameterListener("Width Level", treeStateListener);
    treeState.addParameterListener("Room Scale", treeStateListener);
    treeState.addParameterListener("HF Cut", treeStateListener);

    //create and add parameters for automation(id,name,label,value range, default value, not sure, not sure).
    treeState.createAndAddParameter("Dry/Wet Level", "Dry/Wet Level", "Dry/Wet Level", reverbSliderRange, 100.0f, nullptr, nullptr);
    treeState.createAndAddParameter("Room Size", "Room Size", "Room Size", reverbSliderRange, 50.0f, nullptr, nullptr);
    treeState.createAndAddParameter("Gain", "Gain", "Gain", gainRange, 0.0f, nullptr, nullptr);
    treeState.createAndAddParameter("Damping Level", "Damping Level", "Damping Level", reverbSliderRange, 0.0f, nullptr, nullptr);
    treeState.createAndAddParameter("Width Level", "Width Level", "Width Level", reverbSliderRange, 0.0f, nullptr, nullptr);
    treeState.createAndAddParameter("Room Scale", "Room Scale", "Room Scale", roomScalerange, 0.0f, nullptr, nullptr);
    treeState.createAndAddParameter("HF Cut", "HF Cut", "HF Cut", hfCutRange, 20000.0f, nullptr, nullptr);
    //treeState.createAndAddParameter("Bypass Button", "Bypass Button", "Bypass Button", buttonRange, 0.0f, nullptr, nullptr);
    
    //create parameters for xml storing and retrieval of user settings. Uses getStateInformation and setStateInformation functions.
    
    treeState.state = ValueTree("savedParameters");
    
}

PrideboundReverberationAudioProcessor::~PrideboundReverberationAudioProcessor()
{
}

//==============================================================================
const String PrideboundReverberationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PrideboundReverberationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PrideboundReverberationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PrideboundReverberationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PrideboundReverberationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PrideboundReverberationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PrideboundReverberationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PrideboundReverberationAudioProcessor::setCurrentProgram (int index)
{
}

const String PrideboundReverberationAudioProcessor::getProgramName (int index)
{
    return {};
}

void PrideboundReverberationAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PrideboundReverberationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    previousGain = pow(10,*treeState.getRawParameterValue("Gain")/20);
    
    //initialize reverbObject parameters to treestate values.
    parameters.roomSize = (*treeState.getRawParameterValue("Room Size")/100.0f);
    parameters.dryLevel = (100.0f - *treeState.getRawParameterValue("Dry/Wet Level"))/100.0f;
    parameters.wetLevel = (*treeState.getRawParameterValue("Dry/Wet Level")/100.0f);
    parameters.damping = (*treeState.getRawParameterValue("Damping Level")/100.0f);
    parameters.width = (*treeState.getRawParameterValue("Width Level")/100.0f);
    reverbObject.setParameters(parameters);
    
    if(*treeState.getRawParameterValue("Room Scale") >= 0.0f && *treeState.getRawParameterValue("Room Scale") < 1.0f){
        //set wet and dry scaling for small room
        parameters.wetScale = 2.0f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.4f;
        parameters.roomScale = 0.10f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 1.0f && *treeState.getRawParameterValue("Room Scale") < 2.0f){
        //set wet and dry scaling for tiled room
        parameters.wetScale = 2.0f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.10f;
        parameters.roomScale = 0.15f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 2.0f && *treeState.getRawParameterValue("Room Scale") < 3.0f){
        //set wet and dry scaling for hall
        parameters.wetScale = 2.2f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.275f;
        parameters.roomScale = 0.24f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 3.0f && *treeState.getRawParameterValue("Room Scale") < 4.0f){
        //set wet and dry scaling for reactor
        parameters.wetScale = 2.2f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.5f;
        parameters.roomScale = 0.28f;
        reverbObject.setParameters(parameters);
    }
    
    //set HFCut coefficients and apply them to objects.
    coefficients = IIRCoefficients::makeLowPass(getSampleRate(), *treeState.getRawParameterValue("HF Cut"));
    filterObjectLeft.setCoefficients(coefficients);
    filterObjectRight.setCoefficients(coefficients);
    
   /* //check bypass status on load.
    if(*treeState.getRawParameterValue("Bypass Button") == 0.0f){
        bypass = 0;
    }else{
        bypass = 1;
    }*/
    
}

void PrideboundReverberationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PrideboundReverberationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PrideboundReverberationAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    float currentGain = previousGain = pow(10,*treeState.getRawParameterValue("Gain")/20);
    
    //initialize reverbObject parameters to slider values.
    parameters.roomSize = (*treeState.getRawParameterValue("Room Size")/100.0f);
    parameters.dryLevel = (100.0f - *treeState.getRawParameterValue("Dry/Wet Level"))/100.0f;
    parameters.wetLevel = (*treeState.getRawParameterValue("Dry/Wet Level")/100.0f);
    parameters.damping = (*treeState.getRawParameterValue("Damping Level")/100.0f);
    parameters.width = (*treeState.getRawParameterValue("Width Level")/100.0f);
    reverbObject.setParameters(parameters);
    
    if(*treeState.getRawParameterValue("Room Scale") >= 0.0f && *treeState.getRawParameterValue("Room Scale") < 1.0f){
        //set wet and dry scaling for small room
        parameters.wetScale = 2.0f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.4f;
        parameters.roomScale = 0.10f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 1.0f && *treeState.getRawParameterValue("Room Scale") < 2.0f){
        //set wet and dry scaling for tiled room
        parameters.wetScale = 2.0f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.10f;
        parameters.roomScale = 0.15f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 2.0f && *treeState.getRawParameterValue("Room Scale") < 3.0f){
        //set wet and dry scaling for hall
        parameters.wetScale = 2.2f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.275f;
        parameters.roomScale = 0.24f;
        reverbObject.setParameters(parameters);
    }else if(*treeState.getRawParameterValue("Room Scale") >= 3.0f && *treeState.getRawParameterValue("Room Scale") < 4.0f){
        //set wet and dry scaling for reactor
        parameters.wetScale = 2.2f;
        parameters.dryScale = 2.0f;
        parameters.dampScale = 0.5f;
        parameters.roomScale = 0.28f;
        reverbObject.setParameters(parameters);
    }
    
    //set HFCut coefficients and apply them to objects.
    coefficients = IIRCoefficients::makeLowPass(getSampleRate(), *treeState.getRawParameterValue("HF Cut"));
    filterObjectLeft.setCoefficients(coefficients);
    filterObjectRight.setCoefficients(coefficients);
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
        //applies reverb to every sample
        reverbObject.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1),buffer.getNumSamples());
        
        //applies EQ to left and right channels
        filterObjectLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
        filterObjectRight.processSamples(buffer.getWritePointer(1), buffer.getNumSamples());
        
        //if current gain is not equal to previous gain, slowly ramp gain to new gain.
        if(currentGain == previousGain){
            buffer.applyGain(currentGain);
        }else{
            buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
            previousGain = currentGain;
        }
}

//==============================================================================
bool PrideboundReverberationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PrideboundReverberationAudioProcessor::createEditor()
{
    return new PrideboundReverberationAudioProcessorEditor (*this);
}

//==============================================================================
void PrideboundReverberationAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    ScopedPointer <XmlElement> xml (treeState.state.createXml()); //creates Xml tree based on treeState.state
    copyXmlToBinary(*xml, destData); //Copies Xml element to memory block (*element,memblock)
    
}

void PrideboundReverberationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ScopedPointer<XmlElement> xmlParameters(getXmlFromBinary(data, sizeInBytes));//sets parameters based on xml treeState.state
    
    //error checking
    
    //if xmlParameters is not empty
    if(xmlParameters != nullptr){
        //if xmlParameters has same tag name of treState.state
        if(xmlParameters->hasTagName(treeState.state.getType())){
            treeState.state=ValueTree::fromXml(*xmlParameters);//set treeState to xmlParameters
        }
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PrideboundReverberationAudioProcessor();
}
