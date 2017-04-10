#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarNoadTableComponent.h"
#include "SkoarpuscleTableComponent.h"
#include "KoarTableComponent.h"


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

   

private:

    unique_ptr<SkoarNoadTableComponent> noadComponent;
    unique_ptr<SkoarpuscleTableComponent> skoarpuscleComponent;
    unique_ptr<KoarTableComponent> koarComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarDeets)
};