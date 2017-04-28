#include "SkoarpionsComponent.h"
#include "SkoarpionComponent.h"

//==============================================================================
SkoarpionsComponent* instance = nullptr;

SkoarpionsComponent* SkoarpionsComponent::getInstance() {
    return instance;
}

SkoarpionsComponent::SkoarpionsComponent() :
    combo_h(18),
    combo_pad(6),
    combo_pad_x2(2 * combo_pad),
    combo_h_total(combo_h + combo_pad_x2)
{
    instance = this;

    addAndMakeVisible(skoarpionsComboBox = new ComboBox());
    skoarpionsComboBox->setTooltip(TRANS("Skoarpion"));
    skoarpionsComboBox->setEditableText(false);
    skoarpionsComboBox->setJustificationType(Justification::centredLeft);
    skoarpionsComboBox->setTextWhenNothingSelected(String());
    skoarpionsComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    skoarpionsComboBox->addListener(this);

    setSize(300, 400);
}

SkoarpionsComponent::~SkoarpionsComponent() {
    if (instance == this)
        instance = nullptr;
}

void SkoarpionsComponent::loadSkoar(Skoar* skoar) {
    skoarpions.clearQuick();
    skoarpionsComboBox->clear();
    auto i = 0;
    for (auto skoarpion : skoar->skoarpions) {
        skoarpions.add(skoarpion);
        skoarpionsComboBox->addItem(skoarpion->name.c_str(), ++i);
    }
    skoarpionsComboBox->setSelectedId(1, sendNotification);
    resized();
}

void SkoarpionsComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void SkoarpionsComponent::resized()
{
    auto r = getLocalBounds();
    skoarpionsComboBox->setBounds(combo_pad, combo_pad, r.getWidth() - combo_pad_x2, combo_h);
    r.removeFromTop(combo_h_total);

    if (skoarpionComponent != nullptr)
        skoarpionComponent->setBounds(r);
}


void SkoarpionsComponent::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == skoarpionsComboBox) {
        if (skoarpions.size() > 0) {
            auto skoarpion = skoarpions[skoarpionsComboBox->getSelectedId() - 1];
            if (skoarpionComponent != nullptr) {
                removeChildComponent(skoarpionComponent);
            }
            addAndMakeVisible(skoarpionComponent = new SkoarpionComponent(skoarpion));
            resized();
        }
    }
}

void SkoarpionsComponent::selectNoad(SkoarNoad* noad) {

    if (skoarpionComponent != nullptr) {
        skoarpionComponent->selectNoad(noad);
    }

}


void SkoarpionsComponent::selectNoadite (const SkoarNoadite& noad) {

    if (skoarpionComponent != nullptr)
    {
        skoarpionComponent->selectNoadite (noad);
    }

}

void SkoarpionsComponent::selectSkoarpion(SkoarpionPtr skoarpion, String voice) {

    auto i = 0;
    for (auto x : skoarpions) {
        ++i;
        if (x == skoarpion) {
            skoarpionsComboBox->setSelectedId(i, sendNotificationSync);
            skoarpionComponent->selectVoice(voice);
        }
        
    }
    

}