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
#include "TestoarResultsComponent.h"
//[/Headers]

#include "TestoarResultsToolBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TestoarResultsToolBar::TestoarResultsToolBar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textLabel = new Label ("text",
                                              TRANS("label text")));
    textLabel->setFont (Font (15.00f, Font::plain));
    textLabel->setJustificationType (Justification::centredLeft);
    textLabel->setEditable (false, false, false);
    textLabel->setColour (Label::textColourId, Colours::white);
    textLabel->setColour (TextEditor::textColourId, Colours::black);
    textLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (debugButton = new TextButton ("debugButton"));
    debugButton->setButtonText (TRANS("%"));
    debugButton->addListener (this);


    //[UserPreSize]
    debugButton->setLookAndFeel(&awesome);
    debugButton->setButtonText(CharPointer_UTF16(L"\xf188"));
    titleText = String("");
    countsText = String("");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    testRunning();
    //[/Constructor]
}

TestoarResultsToolBar::~TestoarResultsToolBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textLabel = nullptr;
    debugButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TestoarResultsToolBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff3d3d6f));

    //[UserPaint] Add your own custom painting code here..
    g.fillAll (backgroundColour);
    //[/UserPaint]
}

void TestoarResultsToolBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    textLabel->setBounds (8, 6, 472, 20);
    debugButton->setBounds (getWidth() - 73, 6, 62, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TestoarResultsToolBar::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == debugButton)
    {
        //[UserButtonCode_debugButton] -- add your button handler code here..
        //[/UserButtonCode_debugButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TestoarResultsToolBar::testRunning() {
    backgroundColour = Colour (0xff3d3d6f);
    repaint();
}

void TestoarResultsToolBar::testsPassed() {
    backgroundColour = Colours::darkgreen;
    repaint();
}

void TestoarResultsToolBar::testsFailed() {
    backgroundColour = Colours::darkred;
    repaint();
}

void TestoarResultsToolBar::setTitle(String &s) {
    titleText = s;
    redrawTitle();
}

void TestoarResultsToolBar::setCounts(String& counts) {
    countsText = counts;
    redrawTitle();
}

void TestoarResultsToolBar::redrawTitle() {
    String s;
    if (countsText != "") {
        s = titleText + " " + countsText;
    } 
    else {
        s = titleText;
    }

    textLabel->setText(s, sendNotification);

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TestoarResultsToolBar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff3d3d6f"/>
  <LABEL name="text" id="8610f4b89bc0de1c" memberName="textLabel" virtualName=""
         explicitFocusOrder="0" pos="8 6 472 20" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="debugButton" id="595e046aeba1195b" memberName="debugButton"
              virtualName="" explicitFocusOrder="0" pos="73R 6 62 20" buttonText="%"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
