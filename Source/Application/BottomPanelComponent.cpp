#include "BottomPanelComponent.h"

#include "../Debuggoar/DebuggoarDeetsPanel.h"
#include "../Logging/SkoarLoggerComponent.h"


BottomPanelComponent::BottomPanelComponent() :
    tabs(new TabbedComponent(TabbedButtonBar::Orientation::TabsAtLeft))
{
    addAndMakeVisible(tabs);
    tabs->addTab("logs", Colours::black, new SkoarLoggerComponent(), true);
    tabs->addTab("deets", Colours::black, new DebuggoarDeets(), true);
    tabs->setTabBarDepth(30);
    tabs->setLookAndFeel(&LNF);
    setSize(300, 500);
}

BottomPanelComponent::~BottomPanelComponent() {
}


void BottomPanelComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void BottomPanelComponent::resized()
{
    tabs->setBounds(getLocalBounds());
}

