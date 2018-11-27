#include "TestoarResultsComponent.h"
#include <regex>
#include "../Logging/SkoarLogger.hpp"

#include "TestoarResultsToolBar.h"
#include "../Utility/TestoarUtil.h"

//==============================================================================
TestoarResultsToolBar::TestoarResultsToolBar ()
{
    textLabel.reset (new Label ("text", TRANS ("label text")));
    addAndMakeVisible (textLabel.get());
    textLabel->setFont (Font (15.00f, Font::plain));
    textLabel->setJustificationType (Justification::centredLeft);
    textLabel->setEditable (false, false, false);
    textLabel->setColour (Label::textColourId, Colours::white);
    textLabel->setColour (TextEditor::textColourId, Colours::black);
    textLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    debugButton.reset (new TextButton ("debugButton"));
    addAndMakeVisible (debugButton.get());
    debugButton->setButtonText (TRANS("%"));
    debugButton->addListener (this);
    
    debugButton->setLookAndFeel(&awesome);
    debugButton->setButtonText(L"\xf188");
    titleText = String("");
    countsText = String("");

    setSize (600, 400);

    testRunning();
}

TestoarResultsToolBar::~TestoarResultsToolBar()
{
    textLabel = nullptr;
    debugButton = nullptr;
}

//==============================================================================
void TestoarResultsToolBar::paint (Graphics& g)
{
    g.fillAll (Colour (0xff3d3d6f));
    g.fillAll (backgroundColour);
}

void TestoarResultsToolBar::resized()
{
    textLabel->setBounds (8, 6, 472, 20);
    debugButton->setBounds (getWidth() - 73, 6, 62, 20);
}

void TestoarResultsToolBar::buttonClicked (Button* buttonThatWasClicked)
{

    if (buttonThatWasClicked == debugButton.get())
    {
        TestoarResultsComponent& results (static_cast<TestoarResultsComponent&>(*getParentComponent ()));
        std::string s (results.getResultsText().toStdString());
        std::smatch sm;

        std::regex eUnitTestFile ("SkoarUT<<([^>]*)>\\s*>\\s*S\\s*k\\s*o\\s*a\\s*r\\s*U\\s*T");
        if (std::regex_search (s, sm, eUnitTestFile))
        {
            std::string dirtyFileName (sm.str (1));
            std::regex eDirty ("\\s*[\\n\\r]+\\s*");
            String unitTestFile (std::regex_replace (dirtyFileName, eDirty, ""));

            SkoarLog.i (unitTestFile.toWideCharPointer ());
            EditoarApplication& app (EditoarApplication::getApp ());

            juce::File f (unitTestFile);

            if (f.existsAsFile ())
                app.openFile (f);

            return;

        }

        std::regex eSkoarce (R"delim(SkoarBegin :: "([^"]*)"\s+::\s+SkoarEnd)delim");

        auto reg_flags = std::regex_constants::format_first_only;
        if (std::regex_search (s, sm, eSkoarce, reg_flags))
        {
            std::string dirtyTestName (textLabel->getText ().toStdString ());
            String skoarce (sm.str (1));

            std::regex eDirty ("[^a-zA-Z0-9_]+");
            String testName (std::regex_replace (dirtyTestName, eDirty, "_"));

            EditoarApplication& app(EditoarApplication::getApp ());
            auto p (app.mainWindowList.getFrontmostProject ());
            
            if (p != nullptr)
            {
                auto file = TestoarUtil::createUnitTest (*p, testName, skoarce);
                app.openFile (file);
            }
        }
    }
}

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
    if (countsText != "") 
        s = titleText + " " + countsText;
    else
        s = titleText;

    textLabel->setText(s, sendNotification);

}
