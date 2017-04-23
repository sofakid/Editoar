#pragma once
#include "DeetsTableComponent.h"
#include "SkoarNoadDataModel.h"

class SkoarNoadTableComponent : public DeetsTableComponent
{
public:
    SkoarNoadTableComponent (SkoarNoadPtr noad);
    SkoarNoadTableComponent (const SkoarNoadite& noad);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarNoadTableComponent)
};
