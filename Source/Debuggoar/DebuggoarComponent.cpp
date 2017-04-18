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
    SkoarString skoarce(editor->getDocument ().getAllContent ().toWideCharPointer ());
    
    skoar = new Skoar (skoarce, &SkoarLog);
    auto skoarpions = SkoarpionsComponent::getInstance ();
    if (skoarpions != nullptr)
    {
        skoarpions->loadSkoar (skoar);
    }

    toolbar->loadSkoar (skoar);


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
    session = new DebuggoarSession (toolbar->getVoice (), skoar);
    session->start ();
}

void DebuggoarComponent::focusOnNoad (SkoarNoadPtr p) {
    if (p->size > 0)
        editor->focusOnNoad (p);
}