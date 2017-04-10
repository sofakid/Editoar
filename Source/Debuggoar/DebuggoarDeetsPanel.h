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

    void showNoad(SkoarNoadPtr);
    void showSkoarpuscle(SkoarpusclePtr);
    void showKoar(SkoarKoarPtr);
    void showEvent(SkoarEventPtr);
    void showFairy(SkoarFairyPtr);

private:

    unique_ptr<SkoarNoadTableComponent> noadComponent;
    unique_ptr<SkoarpuscleTableComponent> skoarpuscleComponent;
    unique_ptr<KoarTableComponent> koarComponent;
    unique_ptr<EventTableComponent> eventComponent;
    unique_ptr<FairyTableComponent> fairyComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarDeets)
};