#include "SkoarpionComponent.h"

SkoarpionComponent::SkoarpionComponent(SkoarpionPtr p) :
    skoarpion(p) 
{
    auto voices = p->skoar->get_all_voices();
    auto proj = Skoarpion::get_projections(p, voices);
    projections = new SkoarProjectionsComponent(proj);
    addAndMakeVisible(projections);
    setSize(300, 400);

}

SkoarpionComponent::~SkoarpionComponent() {
    skoarpion = nullptr;
    projections = nullptr;
}

void SkoarpionComponent::paint(Graphics& g)
{
    //g.fillAll(Colours::yellow.withAlpha(0.5f));
}

void SkoarpionComponent::resized()
{
    projections->setBounds(getLocalBounds());
}
