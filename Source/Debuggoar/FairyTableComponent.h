#pragma once
#include "DeetsTableComponent.h"
#include "FairyDataModel.h"
#include "fairy.hpp"

class FairyTableComponent : public DeetsTableComponent {
public:
    FairyTableComponent(SkoarFairyPtr);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FairyTableComponent)
};
