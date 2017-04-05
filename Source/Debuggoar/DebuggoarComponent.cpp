#include "DebuggoarComponent.h"
#include "../Logging/SkoarLogger.hpp"

//==============================================================================
DebuggoarComponent* instance = nullptr;

DebuggoarComponent* DebuggoarComponent::getDebuggoar() {
    return instance;
}

DebuggoarComponent::DebuggoarComponent(SkoarCodeEditorComponent *ed) :
    editor(ed),
    toolbar(new DebuggoarToolbar()),
    popupper(new DebuggoarPopupperComponent()),
    deets(new DebuggoarDeets())
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(editor);
    addAndMakeVisible(deets);

    addChildComponent(popupper);

    setSize(600, 400);

    instance = this;

    skoar = new Skoar(editor->getDocument().getAllContent().toWideCharPointer(), &SkoarLog);
    deets->loadSkoar(skoar);
}

DebuggoarComponent::~DebuggoarComponent()
{
    toolbar = nullptr;
    editor = nullptr;
    popupper = nullptr;
    deets = nullptr;
    instance = nullptr;
    skoar = nullptr;
}

//==============================================================================
void DebuggoarComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void DebuggoarComponent::resized()
{
    auto r = getLocalBounds();
    popupper->setBounds(r);

    toolbar->setBounds (r.removeFromTop(32));

    if (deets != nullptr && deets->isVisible()) {
        deets->setBounds(r.removeFromLeft(300));
    }

    editor->setBounds(r);
}

void DebuggoarComponent::popupNoad(SkoarNoadPtr p, Point<int> pt) {
    popupper->popupNoad(p, pt);

}

void DebuggoarComponent::popupSkoarpuscle(SkoarpusclePtr p, Point<int> pt) {
    popupper->popupSkoarpuscle(p, pt);
}

void DebuggoarComponent::unpop() {
    popupper->unpop();
}