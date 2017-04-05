#include "SkoarNoadTableComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "SkoarNoadDataModel.h"
#include "DebuggoarComponent.h"


SkoarNoadTableComponent::SkoarNoadTableComponent(SkoarNoadPtr p) :
    noad(p)
{

    addAndMakeVisible(groupComponent = new GroupComponent("groupy", TRANS("Noad")));
    groupComponent->setTextLabelPosition(Justification::centredLeft);
    groupComponent->setColour(GroupComponent::outlineColourId, Colour(0x66ffffff));
    groupComponent->setColour(GroupComponent::textColourId, Colours::white);
    
    addAndMakeVisible (table = new TableListBox("noadtable"));

    TableHeaderComponent* header = new TableHeaderComponent();
    header->addColumn ("", SkoarNoadDataModel::EColumn::field, 30);
    header->addColumn ("", SkoarNoadDataModel::EColumn::value, 300);
    header->setColour (ListBox::backgroundColourId, Colours::darkgrey);

    model = new SkoarNoadDataModel(noad);
    table->setHeader (header);
    table->setHeaderHeight (0);
    table->setModel (model);
    table->autoSizeAllColumns();

    setSize(330, 200);
}

SkoarNoadTableComponent::~SkoarNoadTableComponent() {
    noad = nullptr;
}

void SkoarNoadTableComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

#define FUDGE_FACTOR 39
#define FUDGE_FACTOR_TRACTOR 6 
int SkoarNoadTableComponent::getHeightHint() {
    return model->getNumRows() * table->getRowHeight() + FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;
}

void SkoarNoadTableComponent::resized()
{
    auto th = getHeightHint();
    table->setBounds(20, 20, proportionOfWidth(1.0000f) - 34, th - FUDGE_FACTOR - FUDGE_FACTOR_TRACTOR);
    
    groupComponent->setBounds(6, 0, proportionOfWidth(1.0000f) - 12, th - FUDGE_FACTOR_TRACTOR);

}
#undef FUDGE_FACTOR
#undef FUDGE_FACTOR_TRACTOR


void SkoarNoadTableComponent::mouseDown(const MouseEvent& /*event*/) {
    DebuggoarComponent::getDebuggoar()->unpop();
}

