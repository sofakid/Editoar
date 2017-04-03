#include "DebuggoarComponent.h"

//==============================================================================

DebuggoarComponent::DebuggoarComponent(SkoarCodeEditorComponent *ed) :
    editor(ed),
    toolbar(new DebuggoarToolbar()),
    popupper(new DebuggoarPopupperComponent()),
    projections(nullptr)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(editor);
    addAndMakeVisible(popupper);

    setSize(600, 400);
}

DebuggoarComponent::~DebuggoarComponent()
{
    toolbar = nullptr;
    editor = nullptr;
    popupper = nullptr;
    projections = nullptr;
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

    if (projections != nullptr && projections->isVisible()) {
        projections->setBounds(r.removeFromLeft(300));
    }

    editor->setBounds(r);
}
