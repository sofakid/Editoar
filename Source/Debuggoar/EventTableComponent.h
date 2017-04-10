#pragma once
#include "DeetsTableComponent.h"
#include "EventDataModel.h"

class EventTableComponent : public DeetsTableComponent {
public:
    EventTableComponent(SkoarEventPtr);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EventTableComponent)
};
