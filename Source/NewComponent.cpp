/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "NewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NewComponent::NewComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    phaseSlider.reset (new Slider ("phase"));
    addAndMakeVisible (phaseSlider.get());
    phaseSlider->setRange (0, 1, 0.1);
    phaseSlider->setSliderStyle (Slider::LinearHorizontal);
    phaseSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    phaseSlider->addListener (this);

    phaseSlider->setBounds (80, 104, 150, 24);

    phaseLabel.reset (new Label ("phase",
                                 TRANS("phase")));
    addAndMakeVisible (phaseLabel.get());
    phaseLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    phaseLabel->setJustificationType (Justification::centredLeft);
    phaseLabel->setEditable (false, false, false);
    phaseLabel->setColour (TextEditor::textColourId, Colours::black);
    phaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    phaseLabel->setBounds (24, 104, 48, 24);

    wetLabel.reset (new Label ("wet",
                               TRANS("wet\n")));
    addAndMakeVisible (wetLabel.get());
    wetLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    wetLabel->setJustificationType (Justification::centredLeft);
    wetLabel->setEditable (false, false, false);
    wetLabel->setColour (TextEditor::textColourId, Colours::black);
    wetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    wetLabel->setBounds (24, 128, 39, 24);

    wetSlider.reset (new Slider ("wet"));
    addAndMakeVisible (wetSlider.get());
    wetSlider->setRange (0, 1, 0.1);
    wetSlider->setSliderStyle (Slider::LinearHorizontal);
    wetSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    wetSlider->addListener (this);

    wetSlider->setBounds (80, 128, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

NewComponent::~NewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    phaseSlider = nullptr;
    phaseLabel = nullptr;
    wetLabel = nullptr;
    wetSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NewComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NewComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == phaseSlider.get())
    {
        //[UserSliderCode_phaseSlider] -- add your slider handling code here..
        //[/UserSliderCode_phaseSlider]
    }
    else if (sliderThatWasMoved == wetSlider.get())
    {
        //[UserSliderCode_wetSlider] -- add your slider handling code here..
        //[/UserSliderCode_wetSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NewComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="phase" id="58f839eba2162eac" memberName="phaseSlider" virtualName=""
          explicitFocusOrder="0" pos="80 104 150 24" min="0.0" max="1.0"
          int="0.1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="phase" id="fc1df6be37141d83" memberName="phaseLabel" virtualName=""
         explicitFocusOrder="0" pos="24 104 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="phase" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="wet" id="ba1777ac58cf21a3" memberName="wetLabel" virtualName=""
         explicitFocusOrder="0" pos="24 128 39 24" edTextCol="ff000000"
         edBkgCol="0" labelText="wet&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="wet" id="fef12d4b2fcce0c7" memberName="wetSlider" virtualName=""
          explicitFocusOrder="0" pos="80 128 150 24" min="0.0" max="1.0"
          int="0.1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

