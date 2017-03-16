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
void SkoarLoggerComponent::paint (Graphics&)
{
}

#include <ctime>

void SkoarLoggerComponent::resized()
{
    if (SkoarLog.getLevel() == SkoarLog.debug) {
        auto x = clock();
        switch (x % 5) {
        case 0:
        case 1:
            SkoarLog.d(L"w00t", 1, 2.01, "derp", this, x);
            break;
        case 2:
            SkoarLog.i(L"w00t", 1, 2.01, "derp", this, x);
            break;
        case 3:
            SkoarLog.w(L"w00t", 1, 2.01, "derp", this, x);
            break;
        case 4:
            SkoarLog.e(L"w00t", 1, 2.01, "derp", this, x);
            break;
        };
    }
    auto r = getLocalBounds();
    toolbarComponent->setBounds (r.removeFromTop(24));
    logPaneComponent->setBounds (r);
}
