#include "DebuggoarPopupper.h"

DebuggoarPopupperComponent::DebuggoarPopupperComponent() {
    setAlwaysOnTop(true);
}

DebuggoarPopupperComponent::~DebuggoarPopupperComponent() {
}

void DebuggoarPopupperComponent::paint(Graphics& g)
{
    g.fillAll(Colours::green.withAlpha(0.5f));
}

void DebuggoarPopupperComponent::resized()
{
    setBounds(getLocalBounds());
}

void DebuggoarPopupperComponent::popupNoad(SkoarNoadPtr p, Point<int> at) {
    if (noadPop != nullptr) {
        removeChildComponent(noadPop.get());
    }

    setVisible(true);

    noadPop = make_unique<SkoarNoadTableComponent>(p);
    addAndMakeVisible(noadPop.get());
    
    auto rLocal = getLocalBounds();
    auto rNoad = noadPop->getBoundsInParent();
    auto noadHeight = rNoad.getHeight();

    auto x = at.getX();
    auto y = at.getY();

    auto q = y + noadHeight - rLocal.getBottom();

    if (q > 0)
        y -= q;

    noadPop->setBounds(x, y, rNoad.getWidth(), noadHeight);
}

void DebuggoarPopupperComponent::popupSkoarpuscle(SkoarpusclePtr p, Point<int>) {
    if (skoarpusclePop != nullptr) {
        removeChildComponent(skoarpusclePop.get());
    }
    skoarpusclePop = make_unique<SkoarpuscleTableComponent>(p);
    addAndMakeVisible(skoarpusclePop.get());
}
