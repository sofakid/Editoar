#include "FairyCursor.h"
#include "Vision.h"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include <climits>

FairyCursor::FairyCursor (SkoarCodeEditorComponent & ed) :
    editor(ed),
    doc (ed.getDocument ()),
    pos (ed.getDocument (), 0),
    shouldBeVisible (false)
{
}

void FairyCursor::fly_to_offs (const size_t offs)
{
    pos.setPosition (offs > INT_MAX ? 0 : static_cast<int> (offs));
    resized ();
    setVisible (shouldBeVisible);
    startTimer (380);
}

void FairyCursor::fly_to_pos (CodeDocument::Position& dest)
{
    pos = dest;
    resized ();
    setVisible (shouldBeVisible);
    startTimer (380);

}

void FairyCursor::paint (Graphics& g) {
    g.setColour (findColour (CaretComponent::caretColourId, true));
    g.fillRect (getLocalBounds ());
}

void FairyCursor::resized ()
{
    setBounds(editor.getCharacterBounds (pos));
}

void FairyCursor::showFairy ()
{
    shouldBeVisible = true;
}

void FairyCursor::hideFairy ()
{
    shouldBeVisible = false;
}

void FairyCursor::timerCallback ()
{
    setVisible (shouldBeVisible && !isVisible ());
}

