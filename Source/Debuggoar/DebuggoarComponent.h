#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DebuggoarPopupper.h"
#include "noad.hpp"
#include "all_skoarpuscles.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "DebuggoarToolbar.h"
#include "DebuggoarDeetsPanel.h"
#include "DebuggoarSession.h"

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

    void startSession();

    void focusOnNoad(SkoarNoadPtr noad);


private:
    ScopedPointer<DebuggoarSession> session;
    ScopedPointer<SkoarCodeEditorComponent> editor;
    ScopedPointer<DebuggoarToolbar> toolbar;
    ScopedPointer<Skoar> skoar;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarComponent)
};
