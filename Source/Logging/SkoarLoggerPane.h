#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "SkoarLogger.hpp"

class SkoarLoggerPaneTextEditor : public TextEditor {
public:
    SkoarLoggerPaneTextEditor(const String &);
    void mouseUp(const MouseEvent &ev) override;

    bool autoScroll;
    bool wordWrap;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarLoggerPaneTextEditor);
};

class SkoarLoggerPane  : public Component, public ISkoarUiLogger
{
public:
    //==============================================================================
    SkoarLoggerPane ();
    ~SkoarLoggerPane();

    void paint (Graphics& g) override;
    void resized() override;

    void logMsg(String &s, Colour colour) override;

    void clearText();
    
    void setAutoScroll(bool);
    void setWordWrap(bool);


private:
    //==============================================================================
    Font font;
    ScopedPointer<SkoarLoggerPaneTextEditor> logPane;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarLoggerPane)
};
