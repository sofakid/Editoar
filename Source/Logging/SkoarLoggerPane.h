#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "SkoarLogger.hpp"

class SkoarLoggerPane  : public Component, public ISkoarUiLogger
{
public:
    //==============================================================================
    SkoarLoggerPane ();
    ~SkoarLoggerPane();

    void paint (Graphics& g) override;
    void resized() override;

    void logMsg(const std::wstring &s, Colour colour) override;

    void clearText();
    
    void enableWordWrap();
    void disableWordWrap();
    
    void enableAutoscroll();
    void disableAutoscroll();

private:
    //==============================================================================
    Font font;
    ScopedPointer<TextEditor> logPane;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarLoggerPane)
};
