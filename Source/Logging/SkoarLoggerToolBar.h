#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SkoarLogger.hpp"

class SkoarLoggerToolBar  : public Component,
    public Button::Listener,
    public ComboBox::Listener
{
public:
    //==============================================================================
    SkoarLoggerToolBar ();
    ~SkoarLoggerToolBar();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

private:

    //==============================================================================
    ScopedPointer<ToggleButton> autoscrollToggler;
    ScopedPointer<TextButton> saveOutputButton;
    ScopedPointer<TextButton> clearButton;
    ScopedPointer<ComboBox> logLevelComboBox;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarLoggerToolBar)
};