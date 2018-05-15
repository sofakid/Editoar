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

//[Headers] You can add your own extra header files here...
#include "DebuggoarSession.h"
#include "../Playoar/PlayoarSession.h"
//[/Headers]

#include "DebuggoarToolbar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "DebuggoarComponent.h"

static DebuggoarToolbar* instance (nullptr);

DebuggoarToolbar* DebuggoarToolbar::getInstance() {
    return instance;
}

void DebuggoarToolbar::selectSkoarpion (SkoarpionPtr skoarpion, String voice)
{
    int i (0);
    bool found (false);
    for (auto& v : voices)
    {
        ++i;
        if (v == voice)
        {
            found = true;
            break;
        }
    }

    if (!found)
        i = 0;

    auto selected (minstrelComboBox->getSelectedId ());
    if (selected <= 0)
    {
        minstrelComboBox->setSelectedId (i, sendNotification);
        selected = i;
    }

    if (selected == i)
    {
        i = 0;
        found = false;
        for (auto& s : skoarpions)
        {
            ++i;
            if (s == skoarpion)
            {
                found = true;
                break;
            }
        }

        if (!found)
            i = 0;

        selected = skoarpionComboBox->getSelectedId ();
        if (selected <= 0)
            selected = i;

        if (selected != i)
            skoarpionComboBox->setSelectedId (i, sendNotification);

    }
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
    minstrelLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
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

    addAndMakeVisible (skoarpionLabel = new Label ("skoarpionLabel",
                                                   TRANS("Skoarpion:")));
    skoarpionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    skoarpionLabel->setJustificationType (Justification::centredRight);
    skoarpionLabel->setEditable (false, false, false);
    skoarpionLabel->setColour (Label::textColourId, Colours::white);
    skoarpionLabel->setColour (TextEditor::textColourId, Colours::black);
    skoarpionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (skoarpionComboBox = new ComboBox ("skoarpionComboBox"));
    skoarpionComboBox->setEditableText (false);
    skoarpionComboBox->setJustificationType (Justification::centredLeft);
    skoarpionComboBox->setTextWhenNothingSelected (String());
    skoarpionComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    skoarpionComboBox->addListener (this);

    addAndMakeVisible (stepToBeatButton = new TextButton ("stepToBeatButton"));
    stepToBeatButton->setTooltip (TRANS("Step To Beat"));
    stepToBeatButton->setButtonText (TRANS(")"));
    stepToBeatButton->addListener (this);

    addAndMakeVisible (playWithoutDebuggingButton = new TextButton ("playWithoutDebuggingButton"));
    playWithoutDebuggingButton->setTooltip (TRANS("Play Without Debugging"));
    playWithoutDebuggingButton->setButtonText (TRANS(")>"));
    playWithoutDebuggingButton->addListener (this);
    playWithoutDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    playWithoutDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    playWithoutDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    playWithoutDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);


    //[UserPreSize]
    openExtDebuggerButton->setLookAndFeel (&awesome);
    openExtDebuggerButton->setButtonText(L"\xf188");

    continueDebuggingButton->setLookAndFeel (&awesome);
    continueDebuggingButton->setButtonText(L"\xf144");

    stopDebuggingButton->setLookAndFeel (&awesome);
    stopDebuggingButton->setButtonText(L"\xf28d");

    stepInButton->setLookAndFeel (&awesome);
    stepInButton->setButtonText(L"\xf13a");

    stepOutButton->setLookAndFeel (&awesome);
    stepOutButton->setButtonText(L"\xf139");

    stepOverButton->setLookAndFeel (&awesome);
    stepOverButton->setButtonText(L"\xf138");

    playWithoutDebuggingButton->setLookAndFeel (&awesome);
    playWithoutDebuggingButton->setButtonText (L"\xf04b");


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
    skoarpionLabel = nullptr;
    skoarpionComboBox = nullptr;
    stepToBeatButton = nullptr;
    playWithoutDebuggingButton = nullptr;


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
    stopDebuggingButton->setBounds (512, 6, 40, 20);
    minstrelLabel->setBounds (240, 6, 55, 20);
    minstrelComboBox->setBounds (296, 6, 150, 20);
    openExtDebuggerButton->setBounds (getWidth() - 49, 6, 40, 20);
    continueDebuggingButton->setBounds (464, 6, 40, 20);
    skoarpionLabel->setBounds (7, 6, 79, 20);
    skoarpionComboBox->setBounds (87, 6, 150, 20);
    stepToBeatButton->setBounds (getWidth() - 225, 6, 32, 20);
    playWithoutDebuggingButton->setBounds (600, 6, 40, 20);
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
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepIn();
        //[/UserButtonCode_stepInButton]
    }
    else if (buttonThatWasClicked == stepOverButton)
    {
        //[UserButtonCode_stepOverButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepOver();
        //[/UserButtonCode_stepOverButton]
    }
    else if (buttonThatWasClicked == stepOutButton)
    {
        //[UserButtonCode_stepOutButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance ();
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
        auto debuggoar = DebuggoarComponent::getDebuggoar ();
        debuggoar->startSession();
        //[/UserButtonCode_continueDebuggingButton]
    }
    else if (buttonThatWasClicked == stepToBeatButton)
    {
        //[UserButtonCode_stepToBeatButton] -- add your button handler code here..
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepToBeat();
        //[/UserButtonCode_stepToBeatButton]
    }
    else if (buttonThatWasClicked == playWithoutDebuggingButton)
    {
        //[UserButtonCode_playWithoutDebuggingButton] -- add your button handler code here..
        auto debuggoar = DebuggoarComponent::getDebuggoar ();
        debuggoar->playWithoutDebugging ();
        //[/UserButtonCode_playWithoutDebuggingButton]
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
        updateTabs ();
        //[/UserComboBoxCode_minstrelComboBox]
    }
    else if (comboBoxThatHasChanged == skoarpionComboBox)
    {
        //[UserComboBoxCode_skoarpionComboBox] -- add your combo box handling code here..
        updateTabs ();
        //[/UserComboBoxCode_skoarpionComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DebuggoarToolbar::updateTabs () {

    const auto selected_voice (minstrelComboBox->getSelectedId ());
    if (selected_voice <= 0)
        return;

    const auto voice (voices.getUnchecked (selected_voice - 1));
    if (voice == "")
        return;

    const auto selected_skoarpion (skoarpionComboBox->getSelectedId ());
    if (selected_skoarpion <= 0)
        return;

    const auto skoarpion (skoarpions.getUnchecked (selected_skoarpion - 1));
    if (skoarpion == nullptr)
        return;

    auto ast (SkoarASTComponent::getInstance ());
    if (ast != nullptr)
        ast->loadSkoarpion (skoarpion);

    auto projection (SkoarProjectionComponent::getInstance ());
    if (projection != nullptr)
    {
        SkoarString v (voice.toWideCharPointer ());
        projection->loadProjection (Skoarpion::projection (skoarpion, v));
    }
}

String DebuggoarToolbar::getVoice() {
    return minstrelComboBox->getText();
}

SkoarpionPtr DebuggoarToolbar::getSkoarpion () {
    auto id (skoarpionComboBox->getSelectedId ());
    if (id > 0)
        return skoarpions.getUnchecked (id - 1);

    if (skoarpions.size() > 0)
        return skoarpions.getUnchecked (0);

    return nullptr;
}

void DebuggoarToolbar::loadSkoar(Skoar* skoar) {

    const int already_selected_minstrel_id (minstrelComboBox->getSelectedId ());
    const int already_selected_skoarpion_id (skoarpionComboBox->getSelectedId ());

    const String all (L"all");
    const auto already_selected_minstrel (already_selected_minstrel_id > 0 ?
        voices.getUnchecked (already_selected_minstrel_id - 1) : all
    );

    const SkoarString skoar_name (L"skoar");
    const String already_selected_skoarpion (already_selected_skoarpion_id > 0 ?
        skoarpions.getUnchecked (already_selected_skoarpion_id - 1)->name.c_str() : skoar_name.c_str()
    );

    // load minstrels
    minstrelComboBox->clear();
    int i = 0;
    int selected_minstrel = 1;
    voices.clearQuick ();

    for (auto x : skoar->voices) {

        String voice (x.first.c_str ());
        if (voice == "")
            continue;

        minstrelComboBox->addItem(voice, ++i);

        if (already_selected_minstrel == voice)
            selected_minstrel = i;

        voices.add (voice);
    }

    // load skoarpions
    skoarpionComboBox->clear ();
    i = 0;
    auto selected_skoarpion = 1;
    skoarpions.clearQuick ();

    for (auto x : skoar->skoarpions)
    {
        String skoarpion_name (x->name.c_str ());
        if (skoarpion_name == "")
            continue;

        skoarpionComboBox->addItem (skoarpion_name, ++i);

        if (already_selected_skoarpion == skoarpion_name)
            selected_skoarpion = i;

        skoarpions.add (x);
    }

    minstrelComboBox->setSelectedId (selected_minstrel, dontSendNotification);
    skoarpionComboBox->setSelectedId (selected_skoarpion, sendNotification);
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
              virtualName="" explicitFocusOrder="0" pos="512 6 40 20" tooltip="Stop Debugging"
              bgColOff="ff808080" bgColOn="ff808080" textCol="ff000000" textColOn="ffffffff"
              buttonText="[]" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="minstrelLabel" id="c7289d80657b1183" memberName="minstrelLabel"
         virtualName="" explicitFocusOrder="0" pos="240 6 55 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Voice:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="minstrelComboBox" id="a72a491faf27f472" memberName="minstrelComboBox"
            virtualName="" explicitFocusOrder="0" pos="296 6 150 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="openExtDebuggerButton" id="91eb8a63ec94aba2" memberName="openExtDebuggerButton"
              virtualName="" explicitFocusOrder="0" pos="49R 6 40 20" tooltip="Open C++ Debugger"
              buttonText="%" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="continueDebuggingButton" id="7c72eca150a64948" memberName="continueDebuggingButton"
              virtualName="" explicitFocusOrder="0" pos="464 6 40 20" tooltip="Continue"
              bgColOff="ff808080" bgColOn="ff808080" textCol="ff000000" textColOn="ffffffff"
              buttonText=")&gt;" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="skoarpionLabel" id="d1178de96fd98116" memberName="skoarpionLabel"
         virtualName="" explicitFocusOrder="0" pos="7 6 79 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Skoarpion:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="skoarpionComboBox" id="27b93cd8bd15bb1d" memberName="skoarpionComboBox"
            virtualName="" explicitFocusOrder="0" pos="87 6 150 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="stepToBeatButton" id="56083f64c910b9a3" memberName="stepToBeatButton"
              virtualName="" explicitFocusOrder="0" pos="225R 6 32 20" tooltip="Step To Beat"
              buttonText=")" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="playWithoutDebuggingButton" id="36f02a2041b9626e" memberName="playWithoutDebuggingButton"
              virtualName="" explicitFocusOrder="0" pos="600 6 40 20" tooltip="Play Without Debugging"
              bgColOff="ff808080" bgColOn="ff808080" textCol="ff000000" textColOn="ffffffff"
              buttonText=")&gt;" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
