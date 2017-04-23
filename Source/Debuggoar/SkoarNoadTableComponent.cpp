#include "SkoarNoadTableComponent.h"

SkoarNoadTableComponent::SkoarNoadTableComponent (SkoarNoadPtr p) :
    DeetsTableComponent ("Noad", new SkoarNoadDataModel (p))
{
}


SkoarNoadTableComponent::SkoarNoadTableComponent (const SkoarNoadite& p) :
    DeetsTableComponent ("Noadite", new SkoarNoaditeDataModel (p))
{
}