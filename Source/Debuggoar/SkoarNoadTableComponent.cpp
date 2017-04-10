#include "SkoarNoadTableComponent.h"

SkoarNoadTableComponent::SkoarNoadTableComponent(SkoarNoadPtr p) :
    DeetsTableComponent("Noad", new SkoarNoadDataModel(p))
{
}