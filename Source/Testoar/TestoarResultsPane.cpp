#include "TestoarResultsPane.h"
#include "../Logging/SkoarLogger.hpp"

TestoarResultsPaneTextEditor::TestoarResultsPaneTextEditor(const String &name) :
    TextEditor(name) {
}

void TestoarResultsPaneTextEditor::mouseUp(const MouseEvent &) {

    auto x = getHighlightedRegion();

    if (x.getLength() > 0) {
        copyToClipboard();
        auto end = getTotalNumChars() - 1;
        auto r = Range<int>(end, end);
        setScrollToShowCursor(false);
        setHighlightedRegion(r);
        moveCaretToEnd();
        setScrollToShowCursor(true);
    }

}

//==============================================================================
TestoarResultsPane::TestoarResultsPane ()
{

    addAndMakeVisible (resultsPane = new TestoarResultsPaneTextEditor("TestoarResults"));
    resultsPane->setMultiLine (true);
    resultsPane->setReturnKeyStartsNewLine (false);
    resultsPane->setReadOnly (true);
    resultsPane->setScrollbarsShown (true);
    resultsPane->setCaretVisible (true);
    resultsPane->setPopupMenuEnabled (true);
    resultsPane->setColour (TextEditor::textColourId, Colours::aliceblue);
    resultsPane->setColour (TextEditor::backgroundColourId, Colours::black);
    resultsPane->setColour (TextEditor::highlightColourId, Colours::blue);
    resultsPane->setColour (TextEditor::highlightedTextColourId, Colours::yellow);

    resultsPane->setText (String(""));

    setSize (600, 400);

    font.setTypefaceName (Font::getDefaultMonospacedFontName());
    font.setHeight (12);
    resultsPane->applyFontToAllText (font);

}

TestoarResultsPane::~TestoarResultsPane()
{
    resultsPane = nullptr;
}

//==============================================================================
void TestoarResultsPane::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void TestoarResultsPane::resized()
{
    resultsPane->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
}

void TestoarResultsPane::insertText(String &s, Colour colour) {
    resultsPane->moveCaretToEnd();
    resultsPane->setColour (TextEditor::textColourId, colour);
    //resultsPane->insertTextAtCaret (s);
    
    auto wtf = resultsPane->getText();
    resultsPane->setText(wtf + s);

    //SkoarLog.i("wtf", s);
}

String TestoarResultsPane::getResultsText ()
{
    return resultsPane->getText();
}
