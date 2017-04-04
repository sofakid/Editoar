#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DebuggoarPopupper.h"
#include "noad.hpp"
#include "all_skoarpuscles.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "DebuggoarToolbar.h"
#include "DebuggoarDeetsPanel.h"

class DebuggoarComponent  : public Component
{
public:

    static DebuggoarComponent* getDebuggoar();

    //==============================================================================
    DebuggoarComponent(SkoarCodeEditorComponent *ed);
    ~DebuggoarComponent();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

    void popupNoad(SkoarNoadPtr, Point<int>);
    void popupSkoarpuscle(SkoarpusclePtr, Point<int>);

private:
    ScopedPointer<DebuggoarPopupperComponent> popupper;
    ScopedPointer<SkoarCodeEditorComponent> editor;

    ScopedPointer<DebuggoarToolbar> toolbar;
    ScopedPointer<DebuggoarDeets> deets;



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarComponent)
};
