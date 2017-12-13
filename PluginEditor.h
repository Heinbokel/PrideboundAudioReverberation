/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class PrideboundReverberationAudioProcessorEditor  : public AudioProcessorEditor,
                                                     public Slider::Listener,
                                                     public Button::Listener
{
public:
    PrideboundReverberationAudioProcessorEditor (PrideboundReverberationAudioProcessor&);
    ~PrideboundReverberationAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;
    void buttonClicked(Button *button) override;
    
    //sliders
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomScaleSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hfCutSliderAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment; //attachment for slider automation parameters.
    
    //buttons
    //ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> bypassButtonAttachment; //attachment for slider automation parameters.
    /*ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> smallRoomButtonAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> tiledRoomButtonAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> hallButtonAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> reactorButtonAttachment; //attachment for slider automation parameters.
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> radioButtonAttachment; //attachment for slider automation parameters.*/
    


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PrideboundReverberationAudioProcessor& processor;
    
    LookAndFeel_V4 hfCut;
    
    //sliders
    Slider roomSizeSlider;
    Slider dampingSlider;
    Slider wetSlider;
    Slider drySlider;
    Slider widthSlider;
    Slider roomScaleSlider;
    Slider preDelaySlider;
    Slider lowPassSlider;
    Slider gainSlider;
    
    //buttons
    TextButton bypassButton;
    TextButton smallRoomButton;
    TextButton tiledRoomButton;
    TextButton hallButton;
    TextButton reactorButton;
    
    //labels
    Label gainLabel;
    Label roomSizeLabel;
    Label dryLabel;
    Label wetLabel;
    Label widthLabel;
    Label dampingLabel;
    Label preDelayLabel;
    Label lowPassLabel;
    
    //tooltip window
    TooltipWindow tipWindow;
    
    //textEditor
    TextEditor textEditor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrideboundReverberationAudioProcessorEditor)
    
};
