#include "DebuggoarComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "SkoarpionsComponent.h"

//==============================================================================
DebuggoarComponent* instance = nullptr;

DebuggoarComponent* DebuggoarComponent::getDebuggoar() {
    return instance;
}

DebuggoarComponent::DebuggoarComponent(SkoarCodeEditorComponent *ed) :
    editor(ed),
    toolbar(new DebuggoarToolbar()),
    session(nullptr)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(editor);

    setSize(600, 400);

    instance = this;

    skoar = new Skoar(editor->getDocument().getAllContent().toWideCharPointer(), &SkoarLog);
    auto skoarpions = SkoarpionsComponent::getInstance();
    if (skoarpions != nullptr) {
        skoarpions->loadSkoar(skoar);
    }

    toolbar->loadSkoar(skoar);
}

DebuggoarComponent::~DebuggoarComponent()
{
    toolbar = nullptr;
    editor = nullptr;
    instance = nullptr;
    skoar = nullptr;
    session = nullptr;
}

//==============================================================================
void DebuggoarComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void DebuggoarComponent::resized()
{
    auto r = getLocalBounds();
    toolbar->setBounds (r.removeFromTop(32));
    editor->setBounds(r);
}

void DebuggoarComponent::startSession() {
    session = new DebuggoarSession(toolbar->getVoice(), skoar);
    session->start();
}

void DebuggoarComponent::focusOnNoad(SkoarNoadPtr p) {
    if (p->size > 0) {
        editor->getTokeniser()->activate_range(p->offs, p->size);
        editor->resized();
        CodeDocument::Position startPos(editor->getDocument(), p->offs);
        CodeDocument::Position endPos(editor->getDocument(), p->offs + p->size);

        auto startLine = startPos.getLineNumber();
        auto endLine = endPos.getLineNumber();

        Range<int> scrollTo(startLine, endLine);
        editor->scrollToKeepLinesOnScreen(scrollTo);
    }
}