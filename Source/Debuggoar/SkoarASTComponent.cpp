#include "SkoarASTComponent.h"
#include "SkoarpionComponent.h"

//==============================================================================
SkoarASTComponent* instance (nullptr);

SkoarASTComponent* SkoarASTComponent::getInstance () {
    return instance;
}

SkoarASTComponent::SkoarASTComponent ()
{
    instance = this;
    setSize (300, 400);
}

SkoarASTComponent::~SkoarASTComponent () {
    if (instance == this)
        instance = nullptr;
}

void SkoarASTComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SkoarASTComponent::resized ()
{
    auto r (getLocalBounds ());

    if (skoarpionComponent != nullptr)
        skoarpionComponent->setBounds (r);
}

void SkoarASTComponent::loadSkoarpion (SkoarpionPtr skoarpion)
{
    if (skoarpionComponent != nullptr)
        removeChildComponent (skoarpionComponent);
    
    addAndMakeVisible (skoarpionComponent = new SkoarTreeComponent (skoarpion->body));
}

void SkoarASTComponent::selectNoad (SkoarNoad* noad) {

    if (skoarpionComponent != nullptr)
        skoarpionComponent->selectNoad (noad);

}
