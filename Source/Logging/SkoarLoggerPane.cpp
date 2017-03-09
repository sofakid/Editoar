#include "SkoarLoggerPane.h"

//==============================================================================
SkoarLoggerPane::SkoarLoggerPane ()
{

    addAndMakeVisible (logPane = new TextEditor (String()));
    logPane->setMultiLine (true);
    logPane->setReturnKeyStartsNewLine (false);
    logPane->setReadOnly (true);
    logPane->setScrollbarsShown (true);
    logPane->setCaretVisible (false);
    logPane->setPopupMenuEnabled (true);
    logPane->setColour (TextEditor::textColourId, Colours::aliceblue);
    logPane->setColour (TextEditor::backgroundColourId, Colours::black);
    logPane->setText (String());

    setSize (600, 300);

    font.setTypefaceName (Font::getDefaultMonospacedFontName());
    font.setHeight (10);
    logPane->applyFontToAllText (font);

    SkoarLog.setUi(this);
}

SkoarLoggerPane::~SkoarLoggerPane()
{
    logPane = nullptr;
}

//==============================================================================
void SkoarLoggerPane::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void SkoarLoggerPane::resized()
{
    logPane->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
}

void SkoarLoggerPane::clearText() {
    logPane->setText (String());
}

void SkoarLoggerPane::enableWordWrap() {
    logPane->setMultiLine (true, true);
}
void SkoarLoggerPane::disableWordWrap() {
    logPane->setMultiLine (true, false);
}

void SkoarLoggerPane::enableAutoscroll() {
    logPane->setText (String());
}
void SkoarLoggerPane::disableAutoscroll() {
    logPane->setText (String());
}

// implementing ISkoarLog
void SkoarLoggerPane::logMsg(const std::wstring &s, Colour colour) {
    logPane->setColour (TextEditor::textColourId, colour);
    String str (s.c_str());
    logPane->insertTextAtCaret (str);
}