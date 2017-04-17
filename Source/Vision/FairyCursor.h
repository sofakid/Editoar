#pragma once
#include "../jucer_Headers.h"

class SkoarCodeEditorComponent;

class FairyCursor : 
    public Component,
    private Timer
{
public:
    FairyCursor (SkoarCodeEditorComponent& ed);

    void fly_to_offs (const size_t offs);
    void fly_to_pos (CodeDocument::Position & dest);

    void paint (Graphics & g) override;
    void resized () override;


    void showFairy ();
    void hideFairy ();

private:
    bool shouldBeVisible;

    void timerCallback () override;

    SkoarCodeEditorComponent& editor;
    CodeDocument& doc;
    CodeDocument::Position pos;

};

