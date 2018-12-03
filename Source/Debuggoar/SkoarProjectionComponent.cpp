#include "SkoarProjectionComponent.h"
#include "skoarpion.hpp"
#include "koar.hpp"

static SkoarProjectionComponent* instance (nullptr);

// static
SkoarProjectionComponent* SkoarProjectionComponent::getInstance () {
    return instance;
}

SkoarProjectionComponent::SkoarProjectionComponent () :
    projectionComponent (nullptr)
{
    instance = this;
    setSize (300, 400);
}

SkoarProjectionComponent::~SkoarProjectionComponent () {
    if (instance == this)
        instance = nullptr;
}

void SkoarProjectionComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SkoarProjectionComponent::resized ()
{
    auto r = getLocalBounds ();

    if (projectionComponent != nullptr)
        projectionComponent->setBounds (r);
}

void SkoarProjectionComponent::loadProjection (SkoarpionProjectionPtr p)
{
    if (projectionComponent != nullptr)
        removeChildComponent (projectionComponent.get());
    
    if (p != nullptr)
    {
        projectionComponent.reset(new NoaditesListComponent (p));
        addAndMakeVisible (projectionComponent.get());
    }
    
    resized ();
}

void SkoarProjectionComponent::selectNoadite (const SkoarNoadite& noad) {

    if (projectionComponent != nullptr)
        projectionComponent->selectNoadite (noad);

}
