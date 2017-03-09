#include "SkoarLoggerComponent.h"

//==============================================================================
SkoarLoggerComponent::SkoarLoggerComponent ()
{

    addAndMakeVisible (toolbarComponent = new SkoarLoggerToolBar());
    addAndMakeVisible (logPaneComponent = new SkoarLoggerPane());

    setSize (600, 400);
}

SkoarLoggerComponent::~SkoarLoggerComponent()
{
    toolbarComponent = nullptr;
    delete logPaneComponent;
}

//==============================================================================
void SkoarLoggerComponent::paint (Graphics& g)
{
}

void SkoarLoggerComponent::resized()
{
    SkoarLog.d(L"w00t", 1, 2.01, "derp", this);
    auto r = getLocalBounds();
    toolbarComponent->setBounds (r.removeFromTop(24));
    logPaneComponent->setBounds (r);
}
