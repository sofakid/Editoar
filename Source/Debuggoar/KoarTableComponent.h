#pragma once
#include "DeetsTableComponent.h"
#include "KoarDataModel.h"

class KoarTableComponent : public DeetsTableComponent {
public:
    KoarTableComponent(SkoarKoarPtr);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KoarTableComponent)
};
