#include <regex>
#include "SamploarComponent.h"

#include "SamploarToolbarComponent.h"

//==============================================================================
SamploarToolbarComponent::SamploarToolbarComponent ()
{
    samploar = nullptr;

    addAndMakeVisible (playButton = new TextButton ("playButton"));
    playButton->setButtonText (TRANS(">"));
    playButton->addListener (this);

    addAndMakeVisible (stopButton = new TextButton ("stopButton"));
    stopButton->setButtonText (TRANS("[]"));
    stopButton->addListener (this);

    addAndMakeVisible (fileNameLabel = new Label ("fileNameLabel",
                                                  TRANS("File Name:")));
    fileNameLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fileNameLabel->setJustificationType (Justification::centredRight);
    fileNameLabel->setEditable (false, false, false);
    fileNameLabel->setColour (Label::textColourId, Colours::grey);
    fileNameLabel->setColour (TextEditor::textColourId, Colours::black);
    fileNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fileNameValueLabel = new Label ("fileNameValueLabel",
                                                       TRANS("C:\\wavs\\monkeys.wav")));
    fileNameValueLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fileNameValueLabel->setJustificationType (Justification::centredLeft);
    fileNameValueLabel->setEditable (false, false, false);
    fileNameValueLabel->setColour (Label::textColourId, Colours::white);
    fileNameValueLabel->setColour (TextEditor::textColourId, Colours::black);
    fileNameValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instrumentIdLabel = new Label ("instrumentIdLabel",
                                                      TRANS("Instrument ID:")));
    instrumentIdLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentIdLabel->setJustificationType (Justification::centredRight);
    instrumentIdLabel->setEditable (false, false, false);
    instrumentIdLabel->setColour (Label::textColourId, Colours::grey);
    instrumentIdLabel->setColour (TextEditor::textColourId, Colours::black);
    instrumentIdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instrumentIdValueLabel = new Label ("instrumentIdValueLabel",
                                                           TRANS("@monkeys")));
    instrumentIdValueLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentIdValueLabel->setJustificationType (Justification::centredLeft);
    instrumentIdValueLabel->setEditable (true, true, false);
    instrumentIdValueLabel->setColour (Label::textColourId, Colours::white);
    instrumentIdValueLabel->setColour (TextEditor::textColourId, Colours::white);
    instrumentIdValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    instrumentIdValueLabel->setColour (TextEditor::highlightColourId, Colour (0xff000085));
    instrumentIdValueLabel->addListener (this);

    addAndMakeVisible (lengthLabel = new Label ("lengthLabel",
                                                TRANS("Length:")));
    lengthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthLabel->setJustificationType (Justification::centredRight);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (Label::textColourId, Colours::grey);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lengthValueLabel = new Label ("lengthValueLabel",
                                                     TRANS("0:35")));
    lengthValueLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthValueLabel->setJustificationType (Justification::centredLeft);
    lengthValueLabel->setEditable (false, false, false);
    lengthValueLabel->setColour (Label::textColourId, Colours::white);
    lengthValueLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    instrumentIdValueLabel->setColour(TextEditor::highlightedTextColourId, Colours::lightyellow);

    playButton->setLookAndFeel (&awesome);
    playButton->setEnabled (false);
    setPlayButtonAsPlay();

    stopButton->setLookAndFeel (&awesome);
    stopButton->setEnabled (false);
    setStopButtonAsStop();

    setSize (600, 400);
}

SamploarToolbarComponent::~SamploarToolbarComponent()
{
    playButton = nullptr;
    stopButton = nullptr;
    fileNameLabel = nullptr;
    fileNameValueLabel = nullptr;
    instrumentIdLabel = nullptr;
    instrumentIdValueLabel = nullptr;
    lengthLabel = nullptr;
    lengthValueLabel = nullptr;
    samploar = nullptr;
}

//==============================================================================
void SamploarToolbarComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SamploarToolbarComponent::resized()
{
    playButton->setBounds (16, 88, 60, 32);
    stopButton->setBounds (88, 88, 60, 32);
    fileNameLabel->setBounds (8, 8, 104, 24);
    fileNameValueLabel->setBounds (120, 8, getWidth() - 129, 24);
    instrumentIdLabel->setBounds (8, 56, 104, 24);
    instrumentIdValueLabel->setBounds (120, 56, getWidth() - 569, 24);
    lengthLabel->setBounds (8, 32, 104, 24);
    lengthValueLabel->setBounds (120, 32, getWidth() - 777, 24);
}

void SamploarToolbarComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (samploar == nullptr) {
        samploar = static_cast<SamploarComponent*>(getParentComponent());
    }

    if (buttonThatWasClicked == playButton)
    {
        samploar->playButtonClicked();
    }
    else if (buttonThatWasClicked == stopButton)
    {
        samploar->stopButtonClicked();
    }

}

void SamploarToolbarComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (samploar == nullptr) {
        samploar = static_cast<SamploarComponent*>(getParentComponent());
    }

    if (labelThatHasChanged == instrumentIdValueLabel)
    {
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
    }

}

void SamploarToolbarComponent::setPlayButtonEnabled(bool b) {
    playButton->setEnabled (b);
}

void SamploarToolbarComponent::setStopButtonEnabled(bool b) {
    stopButton->setEnabled (b);
}

void SamploarToolbarComponent::setPlayButtonAsPause() {
    playButton->setButtonText(L"\xf04c");
}

void SamploarToolbarComponent::setPlayButtonAsPlay() {
    playButton->setButtonText(L"\xf04b");
}

void SamploarToolbarComponent::setStopButtonAsReset() {
    stopButton->setButtonText(L"\xf049");

}

void SamploarToolbarComponent::setStopButtonAsStop() {
    stopButton->setButtonText(L"\xf04d");
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
