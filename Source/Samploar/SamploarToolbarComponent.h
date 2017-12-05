/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../JuceLibraryCode/JuceHeader.h"

class SamploarComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SamploarToolbarComponent  : public Component,
                                  public ButtonListener,
                                  public LabelListener
{
public:
    //==============================================================================
    SamploarToolbarComponent ();
    ~SamploarToolbarComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPlayButtonEnabled(bool);
    void setStopButtonEnabled(bool);

    void setPlayButtonAsPause();
    void setPlayButtonAsPlay();

    void setStopButtonAsReset();
    void setStopButtonAsStop();

    void setFileName(String fileName);
    void setFileLength(double seconds);
    void setInstrumentId(String id);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void labelTextChanged (Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    String makeValidId(String s);

    class AwesomeButtonsLNF : public LookAndFeel_V3
    {
        Font getTextButtonFont(TextButton&, int buttonHeight) override
        {
            auto fontawesome = Typeface::createSystemTypefaceFor(BinaryData::fontawesomewebfont_ttf, BinaryData::fontawesomewebfont_ttfSize);
            auto size = jmin(15.0f, buttonHeight * 0.6f);
            auto font = Font(fontawesome);
            font.setHeight(size);
            return font;
        }
    };

    AwesomeButtonsLNF awesome;
    SamploarComponent* samploar;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<Label> fileNameLabel;
    ScopedPointer<Label> fileNameValueLabel;
    ScopedPointer<Label> instrumentIdLabel;
    ScopedPointer<Label> instrumentIdValueLabel;
    ScopedPointer<Label> lengthLabel;
    ScopedPointer<Label> lengthValueLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamploarToolbarComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
