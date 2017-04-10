#include "KoarTableComponent.h"

KoarTableComponent::KoarTableComponent(SkoarKoarPtr p) :
    DeetsTableComponent("Koar", new KoarDataModel(p))
{
}