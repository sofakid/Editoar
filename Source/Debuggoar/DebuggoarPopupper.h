#pragma once

#include "SkoarNoadTableComponent.h"
#include "SkoarpuscleTableComponent.h"

class DebuggoarPopupperComponent : public Component {
public:

    DebuggoarPopupperComponent();
    ~DebuggoarPopupperComponent() override;

    void popupNoad(SkoarNoadPtr, Point<int>);
    void popupSkoarpuscle(SkoarpusclePtr, Point<int>);

    void paint(Graphics& g) override;
    void resized() override;

private:
    //OwnedArray<SkoarNoadTableComponent> noadPops;
    //OwnedArray<SkoarpuscleTableComponent> skoarpusclePops;

    unique_ptr<SkoarNoadTableComponent> noadPop;
    unique_ptr<SkoarpuscleTableComponent> skoarpusclePop;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarPopupperComponent)
};