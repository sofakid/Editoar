/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SkoarLoggerPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SkoarLoggerPane::SkoarLoggerPane ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (logPane = new TextEditor ("log pane"));
    logPane->setMultiLine (true);
    logPane->setReturnKeyStartsNewLine (false);
    logPane->setReadOnly (true);
    logPane->setScrollbarsShown (true);
    logPane->setCaretVisible (false);
    logPane->setPopupMenuEnabled (true);
    logPane->setColour (TextEditor::textColourId, Colours::aliceblue);
    logPane->setColour (TextEditor::backgroundColourId, Colours::black);
    logPane->setText (TRANS("D .. derp?\n"
    "I -- dorp dorp.\n"
    "W :: It\'s dorping.\n"
    "E !! DORP!\n"));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 300);


    //[Constructor] You can add your own custom stuff here..
    //logPane->getFont().setTypefaceName(Font::getDefaultMonospacedFontName())
    //[/Constructor]
}

SkoarLoggerPane::~SkoarLoggerPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    logPane = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SkoarLoggerPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SkoarLoggerPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    logPane->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SkoarLoggerPane" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="300">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="log pane" id="6e91949a44bddd6" memberName="logPane" virtualName=""
              explicitFocusOrder="0" pos="0 0 100% 100%" posRelativeH="e2a29767587cfb75"
              textcol="fff0f8ff" bkgcol="ff000000" initialText="D .. derp?&#10;I -- dorp dorp.&#10;W :: It's dorping.&#10;E !! DORP!&#10;"
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
