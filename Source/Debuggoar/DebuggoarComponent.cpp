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
    toolbar(new DebuggoarToolbar())
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
}

DebuggoarComponent::~DebuggoarComponent()
{
    toolbar = nullptr;
    editor = nullptr;
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
    toolbar->setBounds (r.removeFromTop(32));
    editor->setBounds(r);
}
