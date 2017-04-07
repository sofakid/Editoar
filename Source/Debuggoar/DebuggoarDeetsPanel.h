#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "../Debuggoar/SkoarNoadTableComponent.h"
#include "../Debuggoar/SkoarpuscleTableComponent.h"


class DebuggoarDeets : public Component {
public:
    static DebuggoarDeets* getInstance();

    DebuggoarDeets();
    ~DebuggoarDeets();

    void paint(Graphics& g) override;
    void resized() override;

    void showNoad(SkoarNoadPtr);
    void showSkoarpuscle(SkoarpusclePtr);
    //void showNoad(SkoarNoadPtr);
    //void showNoad(SkoarNoadPtr);


private:

    unique_ptr<SkoarNoadTableComponent> noadComponent;
    unique_ptr<SkoarpuscleTableComponent> skoarpuscleComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarDeets)
};