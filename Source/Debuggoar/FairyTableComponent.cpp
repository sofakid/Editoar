#include "FairyTableComponent.h"

FairyTableComponent::FairyTableComponent(SkoarFairyPtr p) :
    DeetsTableComponent("Magical Fairy", new FairyDataModel(p))
{
}