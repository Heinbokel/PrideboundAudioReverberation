/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PrideboundReverberationAudioProcessorEditor::PrideboundReverberationAudioProcessorEditor (PrideboundReverberationAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //editor
    setSize (500, 325); //literally sets the pixel dimensions of the application
    LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Baskerville");
    
    //tooltip window
    tipWindow.setMillisecondsBeforeTipAppears(5000);//how long cursor must hover on object for tooltip to appear
    getLookAndFeel().setColour(TooltipWindow::backgroundColourId, Colours::black);
    getLookAndFeel().setColour(TooltipWindow::outlineColourId, Colours::darkcyan);
    getLookAndFeel().setColour(TooltipWindow::textColourId, Colours::white);
    
    //These attach the sliders to the automation parameters in treeState
    drySliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Dry/Wet Level",drySlider);
    wetSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Wet Level",wetSlider);
    roomSizeSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Room Size",roomSizeSlider);
    dampingSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Damping Level",dampingSlider);
    widthSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Width Level",widthSlider);
    roomScaleSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Room Scale",roomScaleSlider);
    hfCutSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"HF Cut",lowPassSlider);
    gainSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState,"Gain",gainSlider);
        
    //Button attachments
    //bypassButtonAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.treeState,"Bypass Button",bypassButton);
    
    //Slider general
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::darkcyan);//sets colors of slider thumbs.
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId,Colours::darkorange);//sets colors of slider tracks below thumb.
    getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colours::peachpuff);//sets colors of slider tracks above thumb.
    getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::darkcyan);//sets colors of textboxt text.
    //hfCut Slider
    hfCut.setColour(Slider::trackColourId, Colours::darkcyan);//slider tracks below thumb
    hfCut.setColour(Slider::thumbColourId, Colours::darkorange);//sets colors of slider thumbs.
    hfCut.setColour(Slider::backgroundColourId, Colours::lightcyan);//slider tracks above thumb.
    
    //roomSize slider
    roomSizeSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    roomSizeSlider.setRange(0.0f,100.0f,0.01f); //sets range of values the slider can cycle through. (min, max,interval)
    roomSizeSlider.setTextValueSuffix("%");
    //roomSizeSlider.setValue(0.0f);//set default value of slider.
    addAndMakeVisible(roomSizeSlider);//adds the component in the parameter to editor and makes it visible.
    roomSizeSlider.addListener(this); //listens for changes in value.
    
    //gain slider
    gainSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    gainSlider.setRange(-48.0f,6.0f,0.01f); //sets range of values the slider can cycle through. (min, max,interval)
    addAndMakeVisible(gainSlider);//adds the component in the parameter to editor and makes it visible.
    gainSlider.addListener(this); //listens for changes in value.
    
    //dryWet slider
    drySlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    drySlider.setRange(0.0f,100.0f,0.01f); //sets range of values the slider can cycle through. (min, max,interval)
    drySlider.setTextValueSuffix("%");
    //drySlider.setValue(0.0f);//set default value of slider.
    addAndMakeVisible(drySlider);//adds the component in the parameter to editor and makes it visible.
    drySlider.addListener(this); //listens for changes in value.
    
    //wet slider
    /*wetSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    wetSlider.setRange(0.0f,1.0f); //sets range of values the slider can cycle through. (min, max,interval)
   // wetSlider.setValue(0.0f);//set default value of slider.
    addAndMakeVisible(wetSlider);//adds the component in the parameter to editor and makes it visible.
    wetSlider.addListener(this); //listens for changes in value.*/
    
    //damping slider
    dampingSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    dampingSlider.setRange(0.0f,100.0f,0.01f); //sets range of values the slider can cycle through. (min, max,interval)
    dampingSlider.setTextValueSuffix("%");
    //dampingSlider.setValue(0.0f);//set default value of slider.
    addAndMakeVisible(dampingSlider);//adds the component in the parameter to editor and makes it visible.
    dampingSlider.addListener(this); //listens for changes in value.
    
    //width slider
    widthSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    widthSlider.setRange(0.0f,100.0f,0.01f); //sets range of values the slider can cycle through. (min, max,interval)
    widthSlider.setTextValueSuffix("%");
    //widthSlider.setValue(0.0f);//set default value of slider.
    addAndMakeVisible(widthSlider);//adds the component in the parameter to editor and makes it visible.
    widthSlider.addListener(this); //listens for changes in value.
    
    //roomScale slider
    roomScaleSlider.setSliderStyle(juce::Slider::Rotary);//Slider style
    roomScaleSlider.setRange(0.0f,3.0f,1.0f);
    roomScaleSlider.addListener(this);
    addAndMakeVisible(roomScaleSlider);//adds the component in the parameter to editor and makes it visible.
    
    //lowPass slider
    lowPassSlider.setLookAndFeel(&hfCut);
    lowPassSlider.setSliderStyle(juce::Slider::LinearHorizontal);//Slider style
    lowPassSlider.setRange(20.0f,20000.0f, 1.0f);
    lowPassSlider.addListener(this);
    addAndMakeVisible(lowPassSlider);//adds the component in the parameter to editor and makes it visible.
    
    //labels General
    getLookAndFeel().setColour(Label::textColourId, Colours::darkorange);
    getLookAndFeel().setColour(Label::backgroundColourId, Colours::transparentWhite);
    getLookAndFeel().setColour(Label::outlineColourId, Colours::transparentWhite);
    hfCut.setColour(Label::textColourId, Colours::darkorange);
    hfCut.setColour(Label::backgroundColourId, Colours::transparentWhite);
    hfCut.setColour(Label::outlineColourId, Colours::transparentWhite);
    

    //roomSize label
    addAndMakeVisible(roomSizeLabel);
    roomSizeLabel.setText("Room Size", NotificationType::dontSendNotification);
    roomSizeLabel.setJustificationType(Justification::centredBottom);
    roomSizeLabel.attachToComponent(&roomSizeSlider, false); //attaches label to component,(component,onLeft)
    
    //gain label
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::centredBottom);
    gainLabel.attachToComponent(&gainSlider, false); //attaches label to component,(component,onLeft)
    
    //dry label
    addAndMakeVisible(dryLabel);
    dryLabel.setText("Dry/Wet", NotificationType::dontSendNotification);
    dryLabel.setJustificationType(Justification::centredBottom);
    dryLabel.attachToComponent(&drySlider, false); //attaches label to component,(component,onLeft)
    
    //wet label
    addAndMakeVisible(wetLabel);
    wetLabel.setText("Wet", NotificationType::dontSendNotification);
    wetLabel.setJustificationType(Justification::centredBottom);
    wetLabel.attachToComponent(&wetSlider, false); //attaches label to component,(component,onLeft)
    
    //damping label
    addAndMakeVisible(dampingLabel);
    dampingLabel.setText("Damping", NotificationType::dontSendNotification);
    dampingLabel.setJustificationType(Justification::centredBottom);
    dampingLabel.attachToComponent(&dampingSlider, false); //attaches label to component,(component,onLeft)
    
    //width label
    addAndMakeVisible(widthLabel);
    widthLabel.setText("Width", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centredBottom);
    widthLabel.attachToComponent(&widthSlider, false); //attaches label to component,(component,onLeft)
    
    //lowPass label
    lowPassLabel.setLookAndFeel(&hfCut);
    addAndMakeVisible(lowPassLabel);
    lowPassLabel.setText("HF Cut", NotificationType::dontSendNotification);
    lowPassLabel.attachToComponent(&lowPassSlider, true); //attaches label to component,(component,onLeft)
    
    //Slider text box (position,read-only,width,height)
    getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::darkorange);//sets colors of textboxt text.
    getLookAndFeel().setColour(Slider::textBoxBackgroundColourId, Colours::transparentWhite);//sets colors of textboxt background.
    getLookAndFeel().setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);//sets colors of textboxt outline.
    getLookAndFeel().setColour(Label::textWhenEditingColourId, Colours::darkorange);//text color when editing.
    getLookAndFeel().setColour(Label::outlineWhenEditingColourId, Colours::darkorange);//outline color when editing.
    getLookAndFeel().setColour(TextEditor::highlightColourId, Colours::darkcyan);//highlight color when editing.
    hfCut.setColour(Slider::textBoxTextColourId, Colours::darkorange);//sets colors of textboxt text.
    hfCut.setColour(Slider::textBoxBackgroundColourId, Colours::transparentWhite);//sets colors of textboxt background.
    hfCut.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);//sets colors of textboxt outline.
    hfCut.setColour(Label::textWhenEditingColourId, Colours::darkorange);//text color when editing.
    hfCut.setColour(Label::outlineWhenEditingColourId, Colours::darkorange);//outline color when editing.
    hfCut.setColour(TextEditor::highlightColourId, Colours::darkcyan);//highlight color when editing.
    
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    lowPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 25);
    lowPassSlider.setTextValueSuffix(" Hz");

    //ToggleButton General
    getLookAndFeel().setColour(ToggleButton::tickColourId, Colours::darkorange);
    getLookAndFeel().setColour(ToggleButton::tickDisabledColourId, Colours::darkorange);
    getLookAndFeel().setColour(ToggleButton::textColourId,Colours::darkorange);
    
    //TextButton General
    getLookAndFeel().setColour(TextButton::buttonColourId,Colours::black); //sets button background color
    getLookAndFeel().setColour(TextButton::textColourOffId, Colours::grey); // sets button text color when not active
    getLookAndFeel().setColour(TextButton::textColourOnId,Colours::cyan); // sets button text color when active
    
    
    //bypass button
    bypassButton.setButtonText("bypass");
    addAndMakeVisible(bypassButton);
    bypassButton.addListener(this);
    
    //Small Room Button
    smallRoomButton.setButtonText("Small Room"); // sets button text
    addAndMakeVisible(smallRoomButton);
    smallRoomButton.addListener(this);
    smallRoomButton.setRadioGroupId(1);
    
    //Tiled Room Button
    tiledRoomButton.setButtonText("Tiled Room"); // sets button text
    addAndMakeVisible(tiledRoomButton);
    tiledRoomButton.addListener(this);
    tiledRoomButton.setRadioGroupId(1);
    
    //Hall Button
    hallButton.setButtonText("Hall"); // sets button text
    addAndMakeVisible(hallButton);
    hallButton.addListener(this);
    hallButton.setRadioGroupId(1);
    
    //Reactor Button
    reactorButton.setButtonText("Reactor"); // sets button text
    addAndMakeVisible(reactorButton);
    reactorButton.addListener(this);
    reactorButton.setRadioGroupId(1);
    
    //Set buttons to correct toggle when opening GUI.
    if(roomScaleSlider.getValue() >= 0.0f && roomScaleSlider.getValue() < 1.0f){
        buttonClicked(&smallRoomButton);
    }else if(roomScaleSlider.getValue() >= 1.0f && roomScaleSlider.getValue() < 2.0f){
        buttonClicked(&tiledRoomButton);
    }else if(roomScaleSlider.getValue() >= 2.0f && roomScaleSlider.getValue() < 3.0f){
        buttonClicked(&hallButton);
    }else if(roomScaleSlider.getValue() >= 3.0f && roomScaleSlider.getValue() < 4.0f){
        buttonClicked(&reactorButton);
    }
    
    /*//check bypass status on load.
    if(processor.bypass == 0){
        bypassButton.setToggleState(false, dontSendNotification);
    }else{
        bypassButton.setToggleState(true, dontSendNotification);
    }*/
    
}

PrideboundReverberationAudioProcessorEditor::~PrideboundReverberationAudioProcessorEditor()
{
}

//==============================================================================
void PrideboundReverberationAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setOpacity(1);
    g.fillAll(Colours::white); //background color
    Image background = ImageCache::getFromMemory (BinaryData::polyLion2_png, BinaryData::polyLion2_pngSize);
    g.setOpacity(0.2);
    g.drawImageAt(background, 50, 0);
    g.setColour(Colours::black);//font color
    g.setFont(Font("Baskerville",40.0f,Font::plain));//font properties
    g.drawText("PRIDEBOUND AUDIO", 0, 0, 500, 40, Justification::centred);//What font says and where

    
}

void PrideboundReverberationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //sliders
    gainSlider.setBounds(0, 150, 100, 110); //Sets bounds. (from left, from top, width, height).
    roomSizeSlider.setBounds(100, 150, 100, 110); //Sets bounds. (from left, from top, width, height).
    drySlider.setBounds(200, 120, 100, 150); //Sets bounds. (from left, from top, width, height).
    dampingSlider.setBounds(300, 150, 100, 110); //Sets bounds. (from left, from top, width, height).
    widthSlider.setBounds(400, 150, 100, 110); //Sets bounds. (from left, from top, width, height).
    lowPassSlider.setBounds(150, 275, 300, 25); //Sets bounds. (from left, from top, width, height).
    //buttons
    //bypassButton.setBounds(200, 310, 100, 30); //Sets bounds. (from left, from top, width, height).
    smallRoomButton.setBounds(50,50,100,30);//Sets bounds. (from left, from top, width, height).
    tiledRoomButton.setBounds(150,50,100,30);//Sets bounds. (from left, from top, width, height).
    hallButton.setBounds(250,50,100,30);//Sets bounds. (from left, from top, width, height).
    reactorButton.setBounds(350,50,100,30);//Sets bounds. (from left, from top, width, height).
    }

void PrideboundReverberationAudioProcessorEditor::sliderValueChanged(Slider *slider){
    
    if(slider == &roomSizeSlider){
        //Set roomSize to value of roomSizeSlider
        processor.parameters.roomSize = (roomSizeSlider.getValue()/100.0f);
        
        //update reverb parameters
        processor.reverbObject.setParameters(processor.parameters);
        
    }else if(slider == &drySlider){
        //Set dry & wet values
        processor.parameters.wetLevel = (drySlider.getValue()/100.0f);
        processor.parameters.dryLevel = (100.0f - drySlider.getValue())/100.0f;
        
        //update reverb parameters
        processor.reverbObject.setParameters(processor.parameters);
        
    }/*else if(slider == &wetSlider){
        //Set wet to value of wetSlider
        processor.parameters.wetLevel = wetSlider.getValue();
        drySlider.setValue(1 - wetSlider.getValue()); //dry value is opposite of wet
        //update reverb parameters
        processor.reverbObject.setParameters(processor.parameters);
        
    }*/else if(slider == &dampingSlider){
        //Set damping to value of dampingSlider
        processor.parameters.damping = (dampingSlider.getValue()/100.0f);
        
        //update reverb parameters
        processor.reverbObject.setParameters(processor.parameters);
    }else if(slider == &widthSlider){
        //Set width to value of dampingSlider
        processor.parameters.width = (widthSlider.getValue()/100.0f);
        
        //update reverb parameters
        processor.reverbObject.setParameters(processor.parameters);
    }else if(slider == &lowPassSlider){
        if(lowPassSlider.getValue() == 20000.0f){
            processor.filterObjectLeft.makeInactive();
            processor.filterObjectRight.makeInactive();
        }else{
            processor.coefficients = IIRCoefficients::makeLowPass(processor.getSampleRate(), lowPassSlider.getValue());
            processor.filterObjectLeft.setCoefficients(processor.coefficients);
            processor.filterObjectRight.setCoefficients(processor.coefficients);
            
        }
    }else if(slider == &gainSlider){
        //Set volume to value of 10 to the power of (gainSlider value / 20).
        //processor.volume = pow(10, gainSlider.getValue() / 20);
    }else if(slider == &roomScaleSlider){
        //Set buttons to correct toggle when opening GUI.
        if(roomScaleSlider.getValue() >= 0.0f && roomScaleSlider.getValue() < 1.0f){
            buttonClicked(&smallRoomButton);
        }else if(roomScaleSlider.getValue() >= 1.0f && roomScaleSlider.getValue() < 2.0f){
            buttonClicked(&tiledRoomButton);
        }else if(roomScaleSlider.getValue() >= 2.0f && roomScaleSlider.getValue() < 3.0f){
            buttonClicked(&hallButton);
        }else if(roomScaleSlider.getValue() >= 3.0f && roomScaleSlider.getValue() < 4.0f){
            buttonClicked(&reactorButton);
        }
    }
}

void PrideboundReverberationAudioProcessorEditor::buttonClicked(Button *button){
    /*if(button == &bypassButton){
        if(bypassButton.getToggleState()==false){
            bypassButton.setToggleState(true, dontSendNotification);
            processor.bypass = 1;
        }else{
            bypassButton.setToggleState(false, dontSendNotification);
            processor.bypass = 0;
        }
    }else*/ if(button == &smallRoomButton){
            smallRoomButton.setToggleState(true, dontSendNotification); // set this button toggle state to true.
            
            roomScaleSlider.setValue(0.0f); //This is how we load our toggle state through xml
        
            //set wet and dry scaling for small room
            processor.parameters.wetScale = 2.0f;
            processor.parameters.dryScale = 2.0f;
            processor.parameters.dampScale = 0.4f;
            processor.parameters.roomScale = 0.10f;
            processor.reverbObject.setParameters(processor.parameters);
        
        
    }else if(button == &tiledRoomButton){
            tiledRoomButton.setToggleState(true, dontSendNotification); // set this button toggle state to true.
            
            roomScaleSlider.setValue(1.0f);//This is how we load our toggle state through xml
            
            //set wet and dry scaling for tiled room
            processor.parameters.wetScale = 2.0f;
            processor.parameters.dryScale = 2.0f;
            processor.parameters.dampScale = 0.10f;
            processor.parameters.roomScale = 0.15f;
            processor.reverbObject.setParameters(processor.parameters);
        
    }else if(button == &hallButton){
            hallButton.setToggleState(true, dontSendNotification); // set this button toggle state to true.
            
            roomScaleSlider.setValue(2.0f);//This is how we load our toggle state through xml
            
            //set wet and dry scaling for hall
            processor.parameters.wetScale = 2.2f;
            processor.parameters.dryScale = 2.0f;
            processor.parameters.dampScale = 0.275f;
            processor.parameters.roomScale = 0.24f;
            processor.reverbObject.setParameters(processor.parameters);
        
    }else if(button == &reactorButton){
            reactorButton.setToggleState(true, dontSendNotification); // set this button toggle state to true.
            
            roomScaleSlider.setValue(3.0f);//This is how we load our toggle state through xml
            
            //set wet and dry scaling for reactor
            processor.parameters.wetScale = 2.2f;
            processor.parameters.dryScale = 2.0f;
            processor.parameters.dampScale = 0.5f;
            processor.parameters.roomScale = 0.28f;
            processor.reverbObject.setParameters(processor.parameters);
    }
}
