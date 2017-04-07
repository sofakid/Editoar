#include "SkoarpionsComponent.h"
#include "SkoarpionComponent.h"

//==============================================================================
SkoarpionsComponent* instance = nullptr;

SkoarpionsComponent* SkoarpionsComponent::getInstance() {
    return instance;
}

SkoarpionsComponent::SkoarpionsComponent() :
    skoarpionsTabs(nullptr)
{
    instance = this;
    setSize(300, 400);

}

SkoarpionsComponent::~SkoarpionsComponent() {
    instance = nullptr;
}

void SkoarpionsComponent::loadSkoar(Skoar* skoar) {
    skoarpionsTabs = new TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop);
    addAndMakeVisible(skoarpionsTabs);
    auto& skoarpions = skoar->skoarpions;

    for (auto skoarpion : skoarpions) {
        skoarpionsTabs->addTab(skoarpion->name.c_str(),
            Colours::black,
            new SkoarpionComponent(skoarpion),
            true /*deleteWhenNotNeeded*/);
    }
}

void SkoarpionsComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void SkoarpionsComponent::resized()
{
    if (skoarpionsTabs != nullptr) {
        skoarpionsTabs->setBounds(getLocalBounds());
    }
}
