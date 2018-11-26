#include "SkoarLoggerPane.h"

SkoarLoggerPaneTextEditor::SkoarLoggerPaneTextEditor(const String &name) :
    TextEditor(name),
    autoScroll(true),
    wordWrap(false) {
}

void SkoarLoggerPaneTextEditor::mouseUp(const MouseEvent &) {

    auto x = getHighlightedRegion();

    if (x.getLength() > 0) {
        copyToClipboard();
        auto end = getTotalNumChars() - 1;
        auto r = Range<int>(end, end);
        setScrollToShowCursor(false);
        setHighlightedRegion(r);
        moveCaretToEnd();
        setScrollToShowCursor(autoScroll);
    }

}

//==============================================================================
SkoarLoggerPane::SkoarLoggerPane ()
{

    addAndMakeVisible (logPane = new SkoarLoggerPaneTextEditor(String("SkoarLogger")));
    logPane->setMultiLine (true);
    logPane->setReturnKeyStartsNewLine (false);
    logPane->setReadOnly (true);
    logPane->setScrollbarsShown (true);
    logPane->setCaretVisible (false);
    logPane->setPopupMenuEnabled (true);
    logPane->setColour (TextEditor::textColourId, Colours::aliceblue);
    logPane->setColour (TextEditor::backgroundColourId, Colours::black);
    logPane->setColour (TextEditor::highlightColourId, Colours::blue);
    logPane->setColour (TextEditor::highlightedTextColourId, Colours::yellow);

    logPane->setText (String());

    setSize (600, 400);

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

void SkoarLoggerPane::setWordWrap(bool on) {
    logPane->wordWrap = on;
    logPane->setMultiLine (true, on);

}

void SkoarLoggerPane::setAutoScroll(bool on) {
    logPane->autoScroll = on;
    logPane->setScrollToShowCursor(on);
}

// implementing ISkoarUiLoggger
void SkoarLoggerPane::logMsg(String &s, Colour colour) {
    logPane->moveCaretToEnd();
    logPane->setColour(TextEditor::textColourId, colour);
    logPane->insertTextAtCaret (s);
}