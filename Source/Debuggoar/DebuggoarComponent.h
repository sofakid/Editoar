#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DebuggoarPopupper.h"
#include "noad.hpp"
#include "all_skoarpuscles.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "DebuggoarToolbar.h"
#include "../Skoarish/SkoarProjectionsComponent.h"

class DebuggoarComponent  : public Component
{
public:
    //==============================================================================
    DebuggoarComponent(SkoarCodeEditorComponent *ed);
    ~DebuggoarComponent();

    //==============================================================================

    void popupNoad(SkoarNoadPtr, Point<int>);
    void popupSkoarpuscle(SkoarpusclePtr, Point<int>);


    void paint (Graphics& g) override;
    void resized() override;



private:
    ScopedPointer<DebuggoarPopupperComponent> popupper;
    ScopedPointer<SkoarCodeEditorComponent> editor;

    ScopedPointer<DebuggoarToolbar> toolbar;
    ScopedPointer<SkoarProjectionsComponent> projections;



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebuggoarComponent)
};
