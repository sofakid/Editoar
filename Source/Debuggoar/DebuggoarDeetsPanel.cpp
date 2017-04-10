#include "DebuggoarDeetsPanel.h"
#include "SkoarpionComponent.h"

DebuggoarDeets* instance = nullptr;

// static
DebuggoarDeets* DebuggoarDeets::getInstance() {
    return instance;
}

DebuggoarDeets::DebuggoarDeets() :
    noadComponent(nullptr),
    skoarpuscleComponent(nullptr),
    koarComponent(nullptr),
    eventComponent(nullptr)
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

#define NOAD_MIN 400
void DebuggoarDeets::resized()
{
    auto r = getLocalBounds();

    if (noadComponent != nullptr) {
        auto hint = noadComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());
        auto w = max(NOAD_MIN, hint.getWidth());
        
        noadComponent->setBounds(0, 0, w, h);
    }

    if (skoarpuscleComponent != nullptr) {
        int x = 0;
        int y = 0;
        if (noadComponent != nullptr) {
            y = noadComponent->getHeight();
        }
        
        auto hint = skoarpuscleComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());
        auto w = max(NOAD_MIN, hint.getWidth());

        skoarpuscleComponent->setBounds(x, y, w, h);
    }

    if (koarComponent != nullptr) {
        int x = NOAD_MIN;
        if (noadComponent != nullptr) {
            x = max(x, noadComponent->getWidth());
        }
        if (skoarpuscleComponent != nullptr) {
            x = max(x, skoarpuscleComponent->getWidth());
        }

        auto hint = koarComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        koarComponent->setBounds(x, 0, hint.getWidth(), h);
    }

    if (fairyComponent != nullptr) {
        int x = NOAD_MIN;
        if (noadComponent != nullptr) {
            x = max(x, noadComponent->getWidth());
        }
        if (skoarpuscleComponent != nullptr) {
            x = max(x, skoarpuscleComponent->getWidth());
        }
        if (koarComponent != nullptr) {
            x += koarComponent->getWidth();
        }
        
        auto hint = fairyComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        fairyComponent->setBounds(x, 0, hint.getWidth(), h);
    }

    if (eventComponent != nullptr) {
        int x = NOAD_MIN;
        int y = 0;
        if (noadComponent != nullptr) {
            x = max(x, noadComponent->getWidth());
        }
        if (skoarpuscleComponent != nullptr) {
            x = max(x, skoarpuscleComponent->getWidth());
        }
        if (koarComponent != nullptr) {
            x += koarComponent->getWidth();
        }
        if (fairyComponent != nullptr) {
            auto hint = fairyComponent->getBoundsHint();
            y += hint.getHeight();
        }
        auto hint = eventComponent->getBoundsHint();
        auto h = min(r.getHeight(), hint.getHeight());

        eventComponent->setBounds(x, y, hint.getWidth(), h);
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

void DebuggoarDeets::showEvent(SkoarEventPtr koar) {
    if (eventComponent != nullptr) {
        removeChildComponent(eventComponent.get());
    }
    eventComponent = make_unique<EventTableComponent>(koar);
    addAndMakeVisible(eventComponent.get());
    resized();

}

void DebuggoarDeets::showFairy(SkoarFairyPtr fairy) {
    if (fairyComponent != nullptr) {
        removeChildComponent(fairyComponent.get());
    }
    fairyComponent = make_unique<FairyTableComponent>(fairy);
    addAndMakeVisible(fairyComponent.get());
    resized();

}
