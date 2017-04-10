#include "SkoarpuscleTableComponent.h"

SkoarpuscleTableComponent::SkoarpuscleTableComponent(SkoarpusclePtr p) :
    DeetsTableComponent("Skoarpuscle", p == nullptr ? 
        new SkoarpuscleDataModel() : new SkoarpuscleDataModel(p))
{
}
