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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyTheme.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (MaLongDelayAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MaLongDelayAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> dwAttachment;
    std::unique_ptr<SliderAttachment> dtlAttachment;
    std::unique_ptr<SliderAttachment> dtrAttachment;
    std::unique_ptr<SliderAttachment> fblAttachment;
    std::unique_ptr<SliderAttachment> fbrAttachment;

    MyLookAndFeel tema;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> DTLslider;
    std::unique_ptr<juce::Slider> DTRslider;
    std::unique_ptr<juce::Slider> FBLslider;
    std::unique_ptr<juce::Slider> FBRslider;
    std::unique_ptr<juce::Slider> DWslider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

