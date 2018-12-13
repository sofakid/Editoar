#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarNoadTableComponent.h"
#include "SkoarpuscleTableComponent.h"
#include "KoarTableComponent.h"
#include "EventTableComponent.h"
#include "FairyTableComponent.h"


class DebuggoarDeets : public Component {
public:
    static DebuggoarDeets* getInstance();

    DebuggoarDeets();
    ~DebuggoarDeets();

    void paint(Graphics& g) override;
    void resized() override;

    void showNoad (SkoarNoadPtr);
    void showNoadite (const SkoarNoadite&);
    
    void showSkoarpuscle(SkoarpusclePtr);
    void showKoar(SkoarKoarPtr);
    void showEvent(SkoarEventPtr);
    void showFairy(SkoarFairyPtr);

private:

    std::unique_ptr<SkoarNoadTableComponent> noadComponent;
    std::unique_ptr<SkoarpuscleTableComponent> skoarpuscleComponent;
    std::unique_ptr<KoarTableComponent> koarComponent;
    std::unique_ptr<EventTableComponent> eventComponent;
    std::unique_ptr<FairyTableComponent> fairyComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarDeets)
};