#pragma once

#include "SkoarLogger.hpp"
#include "SkoarLoggerToolBar.h"
#include "SkoarLoggerPane.h"

//==============================================================================
class SkoarLoggerComponent  : public Component
{
public:
    //==============================================================================
    SkoarLoggerComponent ();
    ~SkoarLoggerComponent();

    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    ScopedPointer<SkoarLoggerToolBar> toolbarComponent;
    SkoarLoggerPane* logPaneComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarLoggerComponent)
};
