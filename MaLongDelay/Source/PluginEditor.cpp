/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"
#include "MyTheme.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (MaLongDelayAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor (p), valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    DTLslider.reset (new juce::Slider ("DTL"));
    addAndMakeVisible (DTLslider.get());
    DTLslider->setRange (0, 10, 0);
    DTLslider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    DTLslider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    DTLslider->addListener (this);

    DTLslider->setBounds (224, 96, 150, 96);

    DTRslider.reset (new juce::Slider ("DTR"));
    addAndMakeVisible (DTRslider.get());
    DTRslider->setRange (0, 10, 0);
    DTRslider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    DTRslider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    DTRslider->addListener (this);

    DTRslider->setBounds (440, 96, 150, 96);

    FBLslider.reset (new juce::Slider ("FBL"));
    addAndMakeVisible (FBLslider.get());
    FBLslider->setRange (0, 10, 0);
    FBLslider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    FBLslider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    FBLslider->addListener (this);

    FBLslider->setBounds (224, 336, 150, 96);

    FBRslider.reset (new juce::Slider ("FBR"));
    addAndMakeVisible (FBRslider.get());
    FBRslider->setRange (0, 10, 0);
    FBRslider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    FBRslider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    FBRslider->addListener (this);

    FBRslider->setBounds (448, 336, 150, 96);

    DWslider.reset (new juce::Slider ("DRYWET"));
    addAndMakeVisible (DWslider.get());
    DWslider->setRange (0, 10, 0);
    DWslider->setSliderStyle (juce::Slider::LinearHorizontal);
    DWslider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    DWslider->addListener (this);

    DWslider->setBounds (264, 264, 288, 24);


    //[UserPreSize]
    dwAttachment.reset(new SliderAttachment(valueTreeState, "DW", *DWslider));
    dtlAttachment.reset(new SliderAttachment(valueTreeState, "DTLeft", *DTLslider));
    dtrAttachment.reset(new SliderAttachment(valueTreeState, "DTRight", *DTRslider));
    fblAttachment.reset(new SliderAttachment(valueTreeState, "FBLeft", *FBLslider));
    fbrAttachment.reset(new SliderAttachment(valueTreeState, "FBRight", *FBRslider));

    this->setLookAndFeel(&tema);
    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    dwAttachment.reset();
    dtlAttachment.reset();
    dtrAttachment.reset();
    fblAttachment.reset();
    fbrAttachment.reset();

    this->setLookAndFeel(nullptr);
    //[/Destructor_pre]

    DTLslider = nullptr;
    DTRslider = nullptr;
    FBLslider = nullptr;
    FBRslider = nullptr;
    DWslider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 204, y = 4, width = 412, height = 460;
        juce::Colour fillColour1 = juce::Colour (0xffe0ff00), fillColour2 = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             776.0f - 204.0f + x,
                                             512.0f - 4.0f + y,
                                             fillColour2,
                                             152.0f - 204.0f + x,
                                             24.0f - 4.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 228, y = 20, width = 360, height = 30;
        juce::String text (TRANS("MA-LONG DELAY"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (30.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 316, y = 220, width = 200, height = 30;
        juce::String text (TRANS("Dry/Wet"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 196, y = 68, width = 200, height = 30;
        juce::String text (TRANS("DelayTime Left (s)"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 412, y = 68, width = 200, height = 30;
        juce::String text (TRANS("DelayTime Right (s)"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 420, y = 308, width = 200, height = 30;
        juce::String text (TRANS("Feedback Right "));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 196, y = 308, width = 200, height = 30;
        juce::String text (TRANS("Feedback Left "));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == DTLslider.get())
    {
        //[UserSliderCode_DTLslider] -- add your slider handling code here..
        //[/UserSliderCode_DTLslider]
    }
    else if (sliderThatWasMoved == DTRslider.get())
    {
        //[UserSliderCode_DTRslider] -- add your slider handling code here..
        //[/UserSliderCode_DTRslider]
    }
    else if (sliderThatWasMoved == FBLslider.get())
    {
        //[UserSliderCode_FBLslider] -- add your slider handling code here..
        //[/UserSliderCode_FBLslider]
    }
    else if (sliderThatWasMoved == FBRslider.get())
    {
        //[UserSliderCode_FBRslider] -- add your slider handling code here..
        //[/UserSliderCode_FBRslider]
    }
    else if (sliderThatWasMoved == DWslider.get())
    {
        //[UserSliderCode_DWslider] -- add your slider handling code here..
        //[/UserSliderCode_DWslider]
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

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="MaLongDelayAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p), processor (p), valueTreeState (vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="800" initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="204 4 412 460" fill="linear: 776 512, 152 24, 0=ffe0ff00, 1=ff008000"
          hasStroke="0"/>
    <TEXT pos="228 20 360 30" fill="solid: ff000000" hasStroke="0" text="MA-LONG DELAY"
          fontname="Default font" fontsize="30.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="316 220 200 30" fill="solid: ff000000" hasStroke="0" text="Dry/Wet"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="196 68 200 30" fill="solid: ff000000" hasStroke="0" text="DelayTime Left (s)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="412 68 200 30" fill="solid: ff000000" hasStroke="0" text="DelayTime Right (s)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="420 308 200 30" fill="solid: ff000000" hasStroke="0" text="Feedback Right "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="196 308 200 30" fill="solid: ff000000" hasStroke="0" text="Feedback Left "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="DTL" id="e601fa764de265cf" memberName="DTLslider" virtualName=""
          explicitFocusOrder="0" pos="224 96 150 96" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="DTR" id="65f31c4e16f1531b" memberName="DTRslider" virtualName=""
          explicitFocusOrder="0" pos="440 96 150 96" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="FBL" id="2e7e7c82fd5f93fa" memberName="FBLslider" virtualName=""
          explicitFocusOrder="0" pos="224 336 150 96" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="FBR" id="b02ca3eb5f51293a" memberName="FBRslider" virtualName=""
          explicitFocusOrder="0" pos="448 336 150 96" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="DRYWET" id="1beb37ca047239c9" memberName="DWslider" virtualName=""
          explicitFocusOrder="0" pos="264 264 288 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

