#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class TestoarResultsPaneTextEditor : public TextEditor {
public:
    TestoarResultsPaneTextEditor(const String &);
    void mouseUp(const MouseEvent &ev) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestoarResultsPaneTextEditor)
};

class TestoarResultsPane  : public Component
{
public:
    //==============================================================================
    TestoarResultsPane ();
    ~TestoarResultsPane ();

    void paint (Graphics& g) override;
    void resized() override;

    void insertText(String &s, Colour colour);
    String getResultsText ();

private:
    //==============================================================================
    Font font;
    ScopedPointer<TestoarResultsPaneTextEditor> resultsPane;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestoarResultsPane)
};
