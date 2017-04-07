#include "SkoarProjectionsComponent.h"

#include "skoarpion.hpp"
#include "koar.hpp"

SkoarProjectionsComponent::SkoarProjectionsComponent(ListOfSkoarpionProjectionsPtr p) :
    tabby(new TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop)),
    projections(p)
{
    addAndMakeVisible(tabby);
    auto colour = Colours::black;

    for (auto projection : *projections) {
        tabby->addTab(projection->proj->voice->name.c_str(), colour, 
            new SkoarTreeComponent(projection->proj), true);
    }

    setSize(300, 400);
}

SkoarProjectionsComponent::~SkoarProjectionsComponent() {
}


void SkoarProjectionsComponent::paint(Graphics&)
{
}


void SkoarProjectionsComponent::resized()
{
    auto r = getLocalBounds();
    tabby->setBounds(r);
}
