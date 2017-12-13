/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class PrideboundReverberationAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PrideboundReverberationAudioProcessor();
    ~PrideboundReverberationAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    AudioProcessorValueTreeState treeState; //stores parameters for automation in the DAW
    ScopedPointer<AudioProcessorValueTreeState::Listener> treeStateListener; //attachment for listening to parameters.
    
    //==============================================================================
    bool bypass = 0; //global variable to store on/off for bypass. 0 to play, 1 to bypass.
    
    //==============================================================================
    float volume;//sets gain value to go off of.
    float previousGain; //used for gain ramp for smooth transitions between gain
    
    //==============================================================================
    Reverb reverbObject; //contains reverb object which contains parameters for reverb.
    Reverb::Parameters parameters;//roomSize,damping,wetLevel,dryLevel,width,freeze.
    
    
    /*
    float roomSize = 0;//0.0 is small, 1.0 is big.
    float damping = 0;//0.0 is not damped, 1.0 is fully damped.
    float wetLevel = 0;//0.0 is not wet, 1.0 is fully wet.
    float dryLevel = 0;//0.0 is not dry, 1.0 is fully dry.
    float width = 0;//0.0 is thin, 1.0 is very wide.
    float freeze = 0;//<0.5 is normal mode values, >0.5 is continuous feedback loop.
     */
    //=============================================================================
    IIRFilter filterObjectLeft; //contains the filter object which contains parameters for EQ in left channel.
    IIRFilter filterObjectRight; //contains the filter object which contains parameters for EQ in right channel.
    IIRCoefficients coefficients; //makeLowPass is what coefficient we will use.
    float filterQ; //How wide or narrow filter is.
    float preDelay;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrideboundReverberationAudioProcessor)
};
