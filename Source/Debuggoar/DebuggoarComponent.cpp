#include "DebuggoarComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "SkoarpionsComponent.h"

//==============================================================================
DebuggoarComponent* instance = nullptr;

DebuggoarComponent* DebuggoarComponent::getDebuggoar () {
    return instance;
}

const SkoarCodeEditorComponent::ColourScheme & DebuggoarComponent::getColourScheme ()
{
    auto deb = getDebuggoar ();
    return deb->editor->getColourScheme ();
}

DebuggoarComponent::DebuggoarComponent (SkoarCodeEditorComponent *ed, Component* outerEditor) :
    editor (ed),
    documentEditor (outerEditor),
    toolbar (new DebuggoarToolbar ()),
    session (nullptr)
{
    addAndMakeVisible (toolbar);
    addAndMakeVisible (editor);

    instance = this;
    
    reloadSkoar ();

    setSize (600, 400);
}

DebuggoarComponent::~DebuggoarComponent ()
{
    toolbar = nullptr;
    if (instance == this)
        instance = nullptr;

    skoar = nullptr;
    session = nullptr;
    documentEditor = nullptr;
    editor = nullptr;
}

//==============================================================================
void DebuggoarComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void DebuggoarComponent::resized ()
{
    auto r = getLocalBounds ();
    toolbar->setBounds (r.removeFromTop (32));
    editor->setBounds (r);
}

void DebuggoarComponent::startSession () {
    if (session != nullptr)
    {
        session->die ();
        session = nullptr;
    }
    session = new DebuggoarSession (toolbar->getSkoarpion (), toolbar->getVoice (), skoar);
    session->start ();
}

void DebuggoarComponent::focusOnNoad (SkoarNoadPtr p) {
    if (p->size > 0)
        editor->focusOnNoad (p);
}


void DebuggoarComponent::focusOnNoadite (const SkoarNoadite& noadite) {
    editor->focusOnNoadite (noadite);
}

void DebuggoarComponent::selectSkoarpion (SkoarpionPtr skoarpion, String voice)
{
    toolbar->selectSkoarpion (skoarpion, voice);
}

void DebuggoarComponent::resetVision ()
{
    editor->resetVision ();
}

void DebuggoarComponent::sessionEnded ()
{
    resetVision ();
}

void DebuggoarComponent::reloadSkoar () {
    SkoarString skoarce (editor->getDocument ().getAllContent ().toWideCharPointer ());

    skoar = new Skoar (skoarce, &SkoarLog);

    toolbar->loadSkoar (skoar);
}