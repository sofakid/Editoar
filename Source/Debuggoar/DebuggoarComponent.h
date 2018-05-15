#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DebuggoarPopupper.h"
#include "noad.hpp"
#include "all_skoarpuscles.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "DebuggoarToolbar.h"
#include "DebuggoarDeetsPanel.h"
#include "DebuggoarSession.h"
#include "../Vision/VisionCanvas.h"

class DebuggoarComponent : public Component
{
public:

    static DebuggoarComponent* getDebuggoar ();
    static const SkoarCodeEditorComponent::ColourScheme& getColourScheme ();

    //==============================================================================
    DebuggoarComponent (SkoarCodeEditorComponent *ed, Component *outerEditor);
    ~DebuggoarComponent ();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized () override;

    void startSession ();
    void playWithoutDebugging ();

    void focusOnNoad (SkoarNoadPtr noad);
    void focusOnNoadite (const SkoarNoadite& noad);

    void selectSkoarpion (SkoarpionPtr skoarpion, String voice);
    void resetVision ();
    void sessionEnded ();

    void reloadSkoar ();

private:
    ScopedPointer<DebuggoarSession> session;
    ScopedPointer<DebuggoarToolbar> toolbar;
    ScopedPointer<Skoar> skoar;
    ScopedPointer<SkoarLite> skoar_lite;

    SkoarCodeEditorComponent* editor; // documentEditor owns this
    ScopedPointer<Component> documentEditor; // the skoarcodeeditor is inside this 
                                             // object, we keep it around so we can destroy it.
                                             // i assume this is temporary.

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebuggoarComponent)
};
