#include "DebuggoarDeetsPanel.h"
#include "SkoarpionComponent.h"

DebuggoarDeets* instance = nullptr;

// static
DebuggoarDeets* DebuggoarDeets::getInstance() {
    return instance;
}

DebuggoarDeets::DebuggoarDeets()
{
    instance = this;
    setSize(300, 400);
}

DebuggoarDeets::~DebuggoarDeets() {
    instance = nullptr;
}

void DebuggoarDeets::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void DebuggoarDeets::resized()
{
    auto r = getLocalBounds();

    if (noadComponent != nullptr) {

        auto hint = noadComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        noadComponent->setBounds(0, 0, hint.getWidth(), h);

    }

    if (skoarpuscleComponent != nullptr) {
        int x = 0;
        if (noadComponent != nullptr) {
            x = noadComponent->getWidth();
        }
        
        auto hint = skoarpuscleComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        skoarpuscleComponent->setBounds(x, 0, hint.getWidth(), h);
    }

    if (koarComponent != nullptr) {
        int x = 0;
        if (noadComponent != nullptr) {
            x = noadComponent->getWidth();
        }
        if (skoarpuscleComponent != nullptr) {
            x += skoarpuscleComponent->getWidth();
        }

        auto hint = koarComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        koarComponent->setBounds(x, 0, hint.getWidth(), h);
    }
}

void DebuggoarDeets::showNoad(SkoarNoadPtr noad) {
    if (noadComponent != nullptr) {
        removeChildComponent(noadComponent.get());
    }

    noadComponent = make_unique<SkoarNoadTableComponent>(noad);
    addAndMakeVisible(noadComponent.get());
    resized();
}

void DebuggoarDeets::showSkoarpuscle(SkoarpusclePtr skrp) {
    if (skoarpuscleComponent != nullptr) {
        removeChildComponent(skoarpuscleComponent.get());
    }
    skoarpuscleComponent = make_unique<SkoarpuscleTableComponent>(skrp);
    addAndMakeVisible(skoarpuscleComponent.get());
    resized();

}


void DebuggoarDeets::showKoar(SkoarKoarPtr koar) {
    if (koarComponent != nullptr) {
        removeChildComponent(koarComponent.get());
    }
    koarComponent = make_unique<KoarTableComponent>(koar);
    addAndMakeVisible(koarComponent.get());
    resized();

}
