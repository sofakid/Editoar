#include "SkoarpionComponent.h"
#include "skoarpion.hpp"
#include "koar.hpp"

SkoarpionComponent::SkoarpionComponent(SkoarpionPtr skoarpion) :
    combo_h(18),
    combo_pad(6),
    combo_pad_x2(2 * combo_pad),
    combo_h_total(combo_h + combo_pad_x2)
{
    addAndMakeVisible(projectionsComboBox = new ComboBox());
    projectionsComboBox->setTooltip(TRANS("Voice"));
    projectionsComboBox->setEditableText(false);
    projectionsComboBox->setJustificationType(Justification::centredLeft);
    projectionsComboBox->setTextWhenNothingSelected(String());
    projectionsComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    projectionsComboBox->addListener(this);

    auto voices = skoarpion->skoar->get_all_voices();
    auto proj = Skoarpion::get_projections(skoarpion, voices);
    auto i = 0;
    for (auto p : *proj) {
        projections.add(p);
        projectionsComboBox->addItem(
            p->voice_name.c_str(), ++i);
    }
    //projectionsComboBox->setSelectedId(1, sendNotification);

    setSize(300, 400);

}

SkoarpionComponent::~SkoarpionComponent() {
    
}

void SkoarpionComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void SkoarpionComponent::resized()
{
    auto r = getLocalBounds();
    projectionsComboBox->setBounds(combo_pad, combo_pad, r.getWidth() - combo_pad_x2, combo_h);
    r.removeFromTop(combo_h_total);

    if (projectionComponent != nullptr)
        projectionComponent->setBounds(r);
}

void SkoarpionComponent::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == projectionsComboBox) {
        if (projections.size() > 0) {
            auto p = projections[projectionsComboBox->getSelectedId() - 1];
            if (projectionComponent != nullptr) {
                removeChildComponent(projectionComponent);
            }
            addAndMakeVisible(projectionComponent = new NoaditesListComponent(p));
            resized();
        }
    }
}

void SkoarpionComponent::selectNoad(SkoarNoad* noad) {

    if (projectionComponent != nullptr) {
        //projectionComponent->selectNoad(noad);
    }

}


void SkoarpionComponent::selectNoadite (const SkoarNoadite& noad) {

    if (projectionComponent != nullptr)
    {
        projectionComponent->selectNoadite(noad);
    }

}


void SkoarpionComponent::selectVoice(String voice) {

    auto i = 0;
    for (auto x : projections) {
        ++i;
        if (String(x->voice_name.c_str()) == voice) {
            projectionsComboBox->setSelectedId(i, sendNotification);
        }
    }
}