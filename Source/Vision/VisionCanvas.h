#pragma once
#include "../jucer_Headers.h"

#include "skoar.hpp"

#include "VisionSegment.h"
#include "../Logging/SkoarLogger.hpp"
#include "FairyCursor.h"

class VisionCanvas : public Component
{
public:
    SkoarCodeEditorComponent& editor;
    CodeDocument &doc;

    VisionCanvas (SkoarCodeEditorComponent* ed);

    void rebuildSegments ();
    void rebuildFailedParseSegments ();

    void makeSegment (int offs, int size, SkoarStyles::EStyle style);

    void paint (Graphics & g) override;
    void resized () override;

    void reload ();
    void redraw ();
    void highlightSelection ();

    FairyCursor* getFairy ();
    void fly_fairy_to (CodeDocument::Position &pos);

    void showFairy ();
    void hideFairy ();

    void focusOnNoad (SkoarNoadPtr p);
    void focusOnNoadite (const SkoarNoadite& noadite);
    void unfocusOnNoad ();

    void reloadColourScheme ();

private:
    SkoarNoadPtr focusNoad;
    const SkoarNoadite* focusNoadite;

    ScopedPointer<FairyCursor> fairy;
    OwnedArray<VisionSegment> segments;
    std::unique_ptr<SkoarLite> skoar;
    CodeEditorComponent::ColourScheme cs;
};