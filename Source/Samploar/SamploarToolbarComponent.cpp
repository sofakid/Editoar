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
#include <regex>
#include "SamploarComponent.h"
//[/Headers]

#include "SamploarToolbarComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SamploarToolbarComponent::SamploarToolbarComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    samploar = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (playButton = new TextButton ("playButton"));
    playButton->setButtonText (TRANS(">"));
    playButton->addListener (this);

    addAndMakeVisible (stopButton = new TextButton ("stopButton"));
    stopButton->setButtonText (TRANS("[]"));
    stopButton->addListener (this);

    addAndMakeVisible (fileNameLabel = new Label ("fileNameLabel",
                                                  TRANS("File Name:")));
    fileNameLabel->setFont (Font (15.00f, Font::plain));
    fileNameLabel->setJustificationType (Justification::centredRight);
    fileNameLabel->setEditable (false, false, false);
    fileNameLabel->setColour (Label::textColourId, Colours::grey);
    fileNameLabel->setColour (TextEditor::textColourId, Colours::black);
    fileNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fileNameValueLabel = new Label ("fileNameValueLabel",
                                                       TRANS("C:\\wavs\\monkeys.wav")));
    fileNameValueLabel->setFont (Font (15.00f, Font::plain));
    fileNameValueLabel->setJustificationType (Justification::centredLeft);
    fileNameValueLabel->setEditable (false, false, false);
    fileNameValueLabel->setColour (Label::textColourId, Colours::white);
    fileNameValueLabel->setColour (TextEditor::textColourId, Colours::black);
    fileNameValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instrumentIdLabel = new Label ("instrumentIdLabel",
                                                      TRANS("Instrument ID:")));
    instrumentIdLabel->setFont (Font (15.00f, Font::plain));
    instrumentIdLabel->setJustificationType (Justification::centredRight);
    instrumentIdLabel->setEditable (false, false, false);
    instrumentIdLabel->setColour (Label::textColourId, Colours::grey);
    instrumentIdLabel->setColour (TextEditor::textColourId, Colours::black);
    instrumentIdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instrumentIdValueLabel = new Label ("instrumentIdValueLabel",
                                                           TRANS("@monkeys")));
    instrumentIdValueLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    instrumentIdValueLabel->setJustificationType (Justification::centredLeft);
    instrumentIdValueLabel->setEditable (true, true, false);
    instrumentIdValueLabel->setColour (Label::textColourId, Colours::white);
    instrumentIdValueLabel->setColour (TextEditor::textColourId, Colours::white);
    instrumentIdValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    instrumentIdValueLabel->setColour (TextEditor::highlightColourId, Colour (0xff000085));
    instrumentIdValueLabel->addListener (this);

    addAndMakeVisible (lengthLabel = new Label ("lengthLabel",
                                                TRANS("Length:")));
    lengthLabel->setFont (Font (15.00f, Font::plain));
    lengthLabel->setJustificationType (Justification::centredRight);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (Label::textColourId, Colours::grey);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lengthValueLabel = new Label ("lengthValueLabel",
                                                     TRANS("0:35")));
    lengthValueLabel->setFont (Font (15.00f, Font::plain));
    lengthValueLabel->setJustificationType (Justification::centredLeft);
    lengthValueLabel->setEditable (false, false, false);
    lengthValueLabel->setColour (Label::textColourId, Colours::white);
    lengthValueLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    instrumentIdValueLabel->setColour(TextEditor::highlightedTextColourId, Colours::lightyellow);

    playButton->setLookAndFeel (&awesome);
    playButton->setButtonText (CharPointer_UTF16(L"\xf04b"));
    playButton->setEnabled (false);

    stopButton->setLookAndFeel (&awesome);
    stopButton->setButtonText (CharPointer_UTF16(L"\xf04d"));
    stopButton->setEnabled (false);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SamploarToolbarComponent::~SamploarToolbarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    playButton = nullptr;
    stopButton = nullptr;
    fileNameLabel = nullptr;
    fileNameValueLabel = nullptr;
    instrumentIdLabel = nullptr;
    instrumentIdValueLabel = nullptr;
    lengthLabel = nullptr;
    lengthValueLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    samploar = nullptr;
    //[/Destructor]
}

//==============================================================================
void SamploarToolbarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SamploarToolbarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    playButton->setBounds (16, 88, 60, 32);
    stopButton->setBounds (88, 88, 60, 32);
    fileNameLabel->setBounds (8, 8, 104, 24);
    fileNameValueLabel->setBounds (120, 8, getWidth() - 129, 24);
    instrumentIdLabel->setBounds (8, 56, 104, 24);
    instrumentIdValueLabel->setBounds (120, 56, getWidth() - 569, 24);
    lengthLabel->setBounds (8, 32, 104, 24);
    lengthValueLabel->setBounds (120, 32, getWidth() - 777, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SamploarToolbarComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (samploar == nullptr) {
        samploar = static_cast<SamploarComponent*>(getParentComponent());
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        samploar->playButtonClicked();
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        samploar->stopButtonClicked();
        //[/UserButtonCode_stopButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SamploarToolbarComponent::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    if (samploar == nullptr) {
        samploar = static_cast<SamploarComponent*>(getParentComponent());
    }
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == instrumentIdValueLabel)
    {
        //[UserLabelCode_instrumentIdValueLabel] -- add your label text handling code here..
        auto instrument = samploar->getDocument()->getInstrument();

        auto oldInstrumentId = instrument->getId();
        auto attempt = instrumentIdValueLabel->getText();
        auto cleaned = SkoarishInstrument::makeValidId(attempt);

        if (oldInstrumentId != cleaned)
        {
            auto newId = instrument->renameId(attempt);
            instrumentIdValueLabel->setText(newId, dontSendNotification);
        } 
        else
        {
            instrumentIdValueLabel->setText(cleaned, dontSendNotification);
        }

        //[/UserLabelCode_instrumentIdValueLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void SamploarToolbarComponent::setPlayButtonEnabled(bool b) {
    playButton->setEnabled (b);
}

void SamploarToolbarComponent::setStopButtonEnabled(bool b) {
    stopButton->setEnabled (b);
}

void SamploarToolbarComponent::setFileName(String fileName) {
    fileNameValueLabel->setText(fileName, dontSendNotification);
}

String secondsToDurationString(double seconds) {

    int64 sec = (int64) seconds;

    auto hrs = sec / 3600L;
    sec %= 3600L;
    
    auto min = sec / 60L;
    sec %= 60L;

    String s(sec);
    
    if (hrs > 0) {
        s = ((sec < 10) ? ":0" : ":") + s;
        s = ((min < 10) ? ":0" : ":") + String(min) + s;
        s = String(hrs) + s;
    }
    else {
        if (min > 0) {
            s = ((sec < 10) ? String(":0") : String(":")) + s;
            s = ((min < 10) ? String("0") : String(":")) + String(min) + s;
        }
        else {
            s += " sec";
        }
    }

    return s;
}

void SamploarToolbarComponent::setFileLength(double seconds) {
    lengthValueLabel->setText(secondsToDurationString(seconds), dontSendNotification);
}

void SamploarToolbarComponent::setInstrumentId(String id) {
    instrumentIdValueLabel->setText(id, sendNotification);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SamploarToolbarComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000"/>
  <TEXTBUTTON name="playButton" id="8df13766622bf75" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="16 88 60 32" buttonText="&gt;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stopButton" id="e2b6b0a364580007" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="88 88 60 32" buttonText="[]"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="fileNameLabel" id="59cf03366b3b4410" memberName="fileNameLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 104 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="File Name:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="fileNameValueLabel" id="3404a363575e087a" memberName="fileNameValueLabel"
         virtualName="" explicitFocusOrder="0" pos="120 8 129M 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="C:\wavs\monkeys.wav"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="instrumentIdLabel" id="b068a761a3281054" memberName="instrumentIdLabel"
         virtualName="" explicitFocusOrder="0" pos="8 56 104 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Instrument ID:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="instrumentIdValueLabel" id="3f0054f060a5bea6" memberName="instrumentIdValueLabel"
         virtualName="" explicitFocusOrder="0" pos="120 56 569M 24" textCol="ffffffff"
         edTextCol="ffffffff" edBkgCol="0" hiliteCol="ff000085" labelText="@monkeys"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
         justification="33"/>
  <LABEL name="lengthLabel" id="f649dd56a64d8bf" memberName="lengthLabel"
         virtualName="" explicitFocusOrder="0" pos="8 32 104 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Length:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="lengthValueLabel" id="edaf7f94cd3ba042" memberName="lengthValueLabel"
         virtualName="" explicitFocusOrder="0" pos="120 32 777M 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0:35" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
