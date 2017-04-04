#include "DebuggoarDeetsPanel.h"

#include "SkoarpionComponent.h"

DebuggoarDeets::DebuggoarDeets() :
    skoarpionsTabs(nullptr)
{
    setSize(300, 400);
}

DebuggoarDeets::~DebuggoarDeets() {
}

void DebuggoarDeets::loadSkoar(Skoar* skoar) {
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

void DebuggoarDeets::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void DebuggoarDeets::resized()
{
    if (skoarpionsTabs != nullptr) {
        skoarpionsTabs->setBounds(getLocalBounds());

    }
}
