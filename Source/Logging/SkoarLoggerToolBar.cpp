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

#include "SkoarLoggerToolBar.h"
#include "SkoarLoggerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SkoarLoggerToolBar::SkoarLoggerToolBar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (autoscrollToggler = new ToggleButton ("autoscroll toggler"));
    autoscrollToggler->setButtonText (TRANS("autoscroll"));
    autoscrollToggler->addListener (this);
    autoscrollToggler->setToggleState (true, dontSendNotification);
    autoscrollToggler->setColour (ToggleButton::textColourId, Colours::azure);

    addAndMakeVisible (wordWrapToggler = new ToggleButton ("word wrap toggler"));
    wordWrapToggler->setButtonText (TRANS("wrap"));
    wordWrapToggler->addListener (this);
    wordWrapToggler->setColour (ToggleButton::textColourId, Colours::azure);

    addAndMakeVisible (saveOutputButton = new TextButton ("save output button"));
    saveOutputButton->setButtonText (TRANS("save..."));
    saveOutputButton->addListener (this);
    saveOutputButton->setColour (TextButton::buttonColourId, Colour (0xff3d3d6f));
    saveOutputButton->setColour (TextButton::buttonOnColourId, Colours::cornflowerblue);
    saveOutputButton->setColour (TextButton::textColourOffId, Colours::azure);
    saveOutputButton->setColour (TextButton::textColourOnId, Colours::azure);

    addAndMakeVisible (clearButton = new TextButton ("clear button"));
    clearButton->setButtonText (TRANS("clear"));
    clearButton->addListener (this);
    clearButton->setColour (TextButton::buttonColourId, Colour (0xff3d3d6f));
    clearButton->setColour (TextButton::buttonOnColourId, Colours::cornflowerblue);
    clearButton->setColour (TextButton::textColourOffId, Colours::azure);
    clearButton->setColour (TextButton::textColourOnId, Colours::azure);

    addAndMakeVisible (logLevelComboBox = new ComboBox ("level  combo box"));
    logLevelComboBox->setTooltip (TRANS("Log Verbocity"));
    logLevelComboBox->setEditableText (false);
    logLevelComboBox->setJustificationType (Justification::centredLeft);
    logLevelComboBox->setTextWhenNothingSelected (String());
    logLevelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    logLevelComboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 24);


    //[Constructor] You can add your own custom stuff here..

    logLevelComboBox->addItem(TRANS("Debug"), 1);
    logLevelComboBox->addItem(TRANS("Info"), 2);
    logLevelComboBox->addItem(TRANS("Warning"), 3);
    logLevelComboBox->addItem(TRANS("Error"), 4);

    logLevelComboBox->setSelectedId(2, sendNotification);
    //[/Constructor]
}

SkoarLoggerToolBar::~SkoarLoggerToolBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    autoscrollToggler = nullptr;
    wordWrapToggler = nullptr;
    saveOutputButton = nullptr;
    clearButton = nullptr;
    logLevelComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SkoarLoggerToolBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff242424));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SkoarLoggerToolBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    autoscrollToggler->setBounds (80, 3, 80, 18);
    wordWrapToggler->setBounds (160, 3, 64, 18);
    saveOutputButton->setBounds (getWidth() - 6 - 65, 3, 65, 18);
    clearButton->setBounds (getWidth() - 76 - 55, 3, 55, 18);
    logLevelComboBox->setBounds (3, 3, 70, 18);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SkoarLoggerToolBar::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    SkoarLoggerPane* logPane = static_cast<SkoarLoggerPane*>(SkoarLog.getUi());
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == autoscrollToggler)
    {
        //[UserButtonCode_autoscrollToggler] -- add your button handler code here..
        //[/UserButtonCode_autoscrollToggler]
    }
    else if (buttonThatWasClicked == wordWrapToggler)
    {
        //[UserButtonCode_wordWrapToggler] -- add your button handler code here..
        //[/UserButtonCode_wordWrapToggler]
    }
    else if (buttonThatWasClicked == saveOutputButton)
    {
        //[UserButtonCode_saveOutputButton] -- add your button handler code here..
        //[/UserButtonCode_saveOutputButton]
    }
    else if (buttonThatWasClicked == clearButton)
    {
        //[UserButtonCode_clearButton] -- add your button handler code here..
        logPane->clearText();
        //[/UserButtonCode_clearButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SkoarLoggerToolBar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == logLevelComboBox)
    {
        //[UserComboBoxCode_logLevelComboBox] -- add your combo box handling code here..

        switch (logLevelComboBox->getSelectedId())
        {
        case 1:
            SkoarLog.setLevel(ISkoarLog::debug);
            break;
        case 2:
            SkoarLog.setLevel(ISkoarLog::info);
            break;
        case 3:
            SkoarLog.setLevel(ISkoarLog::warning);
            break;
        case 4:
            SkoarLog.setLevel(ISkoarLog::error);
            break;
        default:
            jassertfalse;
        }

        //[/UserComboBoxCode_logLevelComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SkoarLoggerToolBar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="24">
  <BACKGROUND backgroundColour="ff242424"/>
  <TOGGLEBUTTON name="autoscroll toggler" id="248891caaea22b98" memberName="autoscrollToggler"
                virtualName="" explicitFocusOrder="0" pos="80 3 80 18" txtcol="fff0ffff"
                buttonText="autoscroll" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="word wrap toggler" id="2c1d6785f59bd865" memberName="wordWrapToggler"
                virtualName="" explicitFocusOrder="0" pos="160 3 64 18" txtcol="fff0ffff"
                buttonText="wrap" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="save output button" id="479be8de5a48c413" memberName="saveOutputButton"
              virtualName="" explicitFocusOrder="0" pos="6Rr 3 65 18" bgColOff="ff3d3d6f"
              bgColOn="ff6495ed" textCol="fff0ffff" textColOn="fff0ffff" buttonText="save..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="clear button" id="72a38b9d1b191533" memberName="clearButton"
              virtualName="" explicitFocusOrder="0" pos="76Rr 3 55 18" bgColOff="ff3d3d6f"
              bgColOn="ff6495ed" textCol="fff0ffff" textColOn="fff0ffff" buttonText="clear"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="level  combo box" id="e2a29767587cfb75" memberName="logLevelComboBox"
            virtualName="" explicitFocusOrder="0" pos="3 3 70 18" tooltip="Log Verbocity"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
