#include "SkoarLoggerComponent.h"
#include "SkoarLoggerToolBar.h"

//==============================================================================
SkoarLoggerToolBar::SkoarLoggerToolBar ()
{
    addAndMakeVisible (autoscrollToggler = new ToggleButton ("autoscroll toggler"));
    autoscrollToggler->setButtonText (TRANS("autoscroll"));
    autoscrollToggler->addListener (this);
    autoscrollToggler->setToggleState (true, dontSendNotification);
    autoscrollToggler->setColour (ToggleButton::textColourId, Colours::azure);

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
    logLevelComboBox->setTooltip (TRANS("Log Verbosity"));
    logLevelComboBox->setEditableText (false);
    logLevelComboBox->setJustificationType (Justification::centredLeft);
    logLevelComboBox->setTextWhenNothingSelected (String());
    logLevelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    logLevelComboBox->addListener (this);

    setSize (600, 24);

    logLevelComboBox->addItem(TRANS("Debug"), 1);
    logLevelComboBox->addItem(TRANS("Info"), 2);
    logLevelComboBox->addItem(TRANS("Warning"), 3);
    logLevelComboBox->addItem(TRANS("Error"), 4);

    logLevelComboBox->setSelectedId(2, sendNotification);
}

SkoarLoggerToolBar::~SkoarLoggerToolBar()
{
    autoscrollToggler = nullptr;
    saveOutputButton = nullptr;
    clearButton = nullptr;
    logLevelComboBox = nullptr;
}

//==============================================================================
void SkoarLoggerToolBar::paint (Graphics& g)
{
    g.fillAll (Colour (0xff242424));
}

void SkoarLoggerToolBar::resized()
{
    autoscrollToggler->setBounds (80, 3, 80, 18);
    saveOutputButton->setBounds (getWidth() - 6 - 65, 3, 65, 18);
    clearButton->setBounds (getWidth() - 76 - 55, 3, 55, 18);
    logLevelComboBox->setBounds (3, 3, 70, 18);
}

void SkoarLoggerToolBar::buttonClicked (Button* buttonThatWasClicked)
{
    SkoarLoggerPane* logPane = static_cast<SkoarLoggerPane*>(SkoarLog.getUi());

    if (buttonThatWasClicked == autoscrollToggler)
        logPane->setAutoScroll(autoscrollToggler->getToggleState());
    
    else if (buttonThatWasClicked == saveOutputButton)
    {
    }
    
    else if (buttonThatWasClicked == clearButton)
        logPane->clearText();

}

void SkoarLoggerToolBar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{

    if (comboBoxThatHasChanged == logLevelComboBox)
    {

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
    }

}
