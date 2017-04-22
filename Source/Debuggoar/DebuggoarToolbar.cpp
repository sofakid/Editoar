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
#include "DebuggoarSession.h"
//[/Headers]

#include "DebuggoarToolbar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "DebuggoarComponent.h"

DebuggoarToolbar* instance = nullptr;

DebuggoarToolbar* DebuggoarToolbar::getInstance() {
    return instance;
}


//[/MiscUserDefs]

//==============================================================================
DebuggoarToolbar::DebuggoarToolbar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    instance = this;
    //[/Constructor_pre]

    addAndMakeVisible (stepInButton = new TextButton ("stepInButton"));
    stepInButton->setTooltip (TRANS("Step In"));
    stepInButton->setButtonText (TRANS("_"));
    stepInButton->addListener (this);

    addAndMakeVisible (stepOverButton = new TextButton ("stepOverButton"));
    stepOverButton->setTooltip (TRANS("Step Over"));
    stepOverButton->setButtonText (TRANS("->"));
    stepOverButton->addListener (this);

    addAndMakeVisible (stepOutButton = new TextButton ("stepOutButton"));
    stepOutButton->setTooltip (TRANS("Step Out"));
    stepOutButton->setButtonText (TRANS("^"));
    stepOutButton->addListener (this);

    addAndMakeVisible (stopDebuggingButton = new TextButton ("stopDebuggingButton"));
    stopDebuggingButton->setTooltip (TRANS("Stop Debugging"));
    stopDebuggingButton->setButtonText (TRANS("[]"));
    stopDebuggingButton->addListener (this);
    stopDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    stopDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    stopDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    stopDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (minstrelLabel = new Label ("minstrelLabel",
                                                  TRANS("Voice:")));
    minstrelLabel->setFont (Font (15.00f, Font::plain));
    minstrelLabel->setJustificationType (Justification::centredRight);
    minstrelLabel->setEditable (false, false, false);
    minstrelLabel->setColour (Label::textColourId, Colours::white);
    minstrelLabel->setColour (TextEditor::textColourId, Colours::black);
    minstrelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (minstrelComboBox = new ComboBox ("minstrelComboBox"));
    minstrelComboBox->setEditableText (false);
    minstrelComboBox->setJustificationType (Justification::centredLeft);
    minstrelComboBox->setTextWhenNothingSelected (String());
    minstrelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    minstrelComboBox->addListener (this);

    addAndMakeVisible (openExtDebuggerButton = new TextButton ("openExtDebuggerButton"));
    openExtDebuggerButton->setTooltip (TRANS("Open C++ Debugger"));
    openExtDebuggerButton->setButtonText (TRANS("%"));
    openExtDebuggerButton->addListener (this);

    addAndMakeVisible (continueDebuggingButton = new TextButton ("continueDebuggingButton"));
    continueDebuggingButton->setTooltip (TRANS("Continue"));
    continueDebuggingButton->setButtonText (TRANS(")>"));
    continueDebuggingButton->addListener (this);
    continueDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    continueDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    continueDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    continueDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);


    //[UserPreSize]
    openExtDebuggerButton->setLookAndFeel (&awesome);
    openExtDebuggerButton->setButtonText(CharPointer_UTF16(L"\xf188"));

    continueDebuggingButton->setLookAndFeel (&awesome);
    continueDebuggingButton->setButtonText(CharPointer_UTF16(L"\xf144"));

    stopDebuggingButton->setLookAndFeel (&awesome);
    stopDebuggingButton->setButtonText(CharPointer_UTF16(L"\xf28d"));

    stepInButton->setLookAndFeel (&awesome);
    stepInButton->setButtonText(CharPointer_UTF16(L"\xf13a"));

    stepOutButton->setLookAndFeel (&awesome);
    stepOutButton->setButtonText(CharPointer_UTF16(L"\xf139"));

    stepOverButton->setLookAndFeel (&awesome);
    stepOverButton->setButtonText(CharPointer_UTF16(L"\xf138"));


    //[/UserPreSize]

    setSize (600, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

DebuggoarToolbar::~DebuggoarToolbar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    instance = nullptr;
    //[/Destructor_pre]

    stepInButton = nullptr;
    stepOverButton = nullptr;
    stepOutButton = nullptr;
    stopDebuggingButton = nullptr;
    minstrelLabel = nullptr;
    minstrelComboBox = nullptr;
    openExtDebuggerButton = nullptr;
    continueDebuggingButton = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DebuggoarToolbar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff222222));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DebuggoarToolbar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    stepInButton->setBounds (getWidth() - 185, 6, 32, 20);
    stepOverButton->setBounds (getWidth() - 145, 6, 32, 20);
    stepOutButton->setBounds (getWidth() - 105, 6, 32, 20);
    stopDebuggingButton->setBounds (344, 6, 40, 20);
    minstrelLabel->setBounds (8, 6, 79, 20);
    minstrelComboBox->setBounds (88, 6, 150, 20);
    openExtDebuggerButton->setBounds (getWidth() - 49, 6, 40, 20);
    continueDebuggingButton->setBounds (296, 6, 40, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DebuggoarToolbar::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == stepInButton)
    {
        //[UserButtonCode_stepInButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance();
        if (x != nullptr)
            x->stepIn();
        //[/UserButtonCode_stepInButton]
    }
    else if (buttonThatWasClicked == stepOverButton)
    {
        //[UserButtonCode_stepOverButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance();
        if (x != nullptr)
            x->stepOver();
        //[/UserButtonCode_stepOverButton]
    }
    else if (buttonThatWasClicked == stepOutButton)
    {
        //[UserButtonCode_stepOutButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance();
        if (x != nullptr)
            x->stepOut();
        
        //[/UserButtonCode_stepOutButton]
    }
    else if (buttonThatWasClicked == stopDebuggingButton)
    {
        //[UserButtonCode_stopDebuggingButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stop ();
        //[/UserButtonCode_stopDebuggingButton]
    }
    else if (buttonThatWasClicked == openExtDebuggerButton)
    {
        //[UserButtonCode_openExtDebuggerButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->cpp_breakpoint ();
        //[/UserButtonCode_openExtDebuggerButton]
    }
    else if (buttonThatWasClicked == continueDebuggingButton)
    {
        //[UserButtonCode_continueDebuggingButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance();
        if (x != nullptr)
            x->continueRunning();
        else
        {
            auto debuggoar = DebuggoarComponent::getDebuggoar();
            debuggoar->startSession();
        }

        //[/UserButtonCode_continueDebuggingButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void DebuggoarToolbar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == minstrelComboBox)
    {
        //[UserComboBoxCode_minstrelComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_minstrelComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String DebuggoarToolbar::getVoice() {
    return minstrelComboBox->getText();
}

void DebuggoarToolbar::loadSkoar(Skoar* skoar) {
    minstrelComboBox->clear();
    int i = 0;
    for (auto voice : skoar->voices) {
        minstrelComboBox->addItem(voice.first.c_str(), ++i);
    }
    minstrelComboBox->setSelectedId(1, dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DebuggoarToolbar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="32">
  <BACKGROUND backgroundColour="ff222222"/>
  <TEXTBUTTON name="stepInButton" id="909e9dcb9b6b4c62" memberName="stepInButton"
              virtualName="" explicitFocusOrder="0" pos="185R 6 32 20" tooltip="Step In"
              buttonText="_" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stepOverButton" id="d56b77bf5a3ed385" memberName="stepOverButton"
              virtualName="" explicitFocusOrder="0" pos="145R 6 32 20" tooltip="Step Over"
              buttonText="-&gt;" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stepOutButton" id="79810f1a7ad348f0" memberName="stepOutButton"
              virtualName="" explicitFocusOrder="0" pos="105R 6 32 20" tooltip="Step Out"
              buttonText="&#94;" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stopDebuggingButton" id="a45ece5ceebbbd29" memberName="stopDebuggingButton"
              virtualName="" explicitFocusOrder="0" pos="344 6 40 20" tooltip="Stop Debugging"
              bgColOff="ff808080" bgColOn="ff808080" textCol="ff000000" textColOn="ffffffff"
              buttonText="[]" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="minstrelLabel" id="c7289d80657b1183" memberName="minstrelLabel"
         virtualName="" explicitFocusOrder="0" pos="8 6 79 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Minstrel:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="minstrelComboBox" id="a72a491faf27f472" memberName="minstrelComboBox"
            virtualName="" explicitFocusOrder="0" pos="88 6 150 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="openExtDebuggerButton" id="91eb8a63ec94aba2" memberName="openExtDebuggerButton"
              virtualName="" explicitFocusOrder="0" pos="49R 6 40 20" tooltip="Open C++ Debugger"
              buttonText="%" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="continueDebuggingButton" id="7c72eca150a64948" memberName="continueDebuggingButton"
              virtualName="" explicitFocusOrder="0" pos="296 6 40 20" tooltip="Continue"
              bgColOff="ff808080" bgColOn="ff808080" textCol="ff000000" textColOn="ffffffff"
              buttonText=")&gt;" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
