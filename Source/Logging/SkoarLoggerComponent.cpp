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
    SkoarLog.i(L"w00t");
    auto r = getLocalBounds();
    toolbarComponent->setBounds (r.removeFromTop(24));
    logPaneComponent->setBounds (r);
}
