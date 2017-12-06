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
#include "SkoarASTComponent.h"
#include "SkoarProjectionComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DebuggoarToolbar  : public Component,
                          public ButtonListener,
                          public ComboBoxListener
{
public:
    //==============================================================================
    DebuggoarToolbar ();
    ~DebuggoarToolbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    class AwesomeButtonsLNF : public LookAndFeel_V3
    {
        Font getTextButtonFont (TextButton&, int buttonHeight) override
        {
            auto fontawesome = Typeface::createSystemTypefaceFor (BinaryData::fontawesomewebfont_ttf, BinaryData::fontawesomewebfont_ttfSize);
            auto size = jmin (15.0f, buttonHeight * 0.6f);
            auto font = Font (fontawesome);
            font.setHeight (size);
            return font;
        }
    };

    AwesomeButtonsLNF awesome;
    void updateTabs ();
    String getVoice ();
    SkoarpionPtr getSkoarpion ();
    void loadSkoar (Skoar*);
    static DebuggoarToolbar* getInstance ();
    void selectSkoarpion (SkoarpionPtr skoarpion, String voice);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Array<SkoarpionPtr> skoarpions;
    Array<String> voices;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> stepInButton;
    ScopedPointer<TextButton> stepOverButton;
    ScopedPointer<TextButton> stepOutButton;
    ScopedPointer<TextButton> stopDebuggingButton;
    ScopedPointer<Label> minstrelLabel;
    ScopedPointer<ComboBox> minstrelComboBox;
    ScopedPointer<TextButton> openExtDebuggerButton;
    ScopedPointer<TextButton> continueDebuggingButton;
    ScopedPointer<Label> skoarpionLabel;
    ScopedPointer<ComboBox> skoarpionComboBox;
    ScopedPointer<TextButton> stepToBeatButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebuggoarToolbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
