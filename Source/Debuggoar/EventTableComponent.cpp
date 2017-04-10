#include "EventTableComponent.h"

EventTableComponent::EventTableComponent(SkoarEventPtr p) :
    DeetsTableComponent("Event", new EventDataModel(p))
{
}