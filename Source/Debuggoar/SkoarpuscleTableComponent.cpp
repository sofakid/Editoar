
#include "SkoarpuscleTableComponent.h"
#include "../Logging/SkoarLogger.hpp"

SkoarpuscleTableComponent::SkoarpuscleTableComponent(SkoarpusclePtr p) {

    addAndMakeVisible(groupComponent = new GroupComponent("groupy",
        TRANS("Skoarpuscle")));
    groupComponent->setTextLabelPosition(Justification::centredLeft);
    groupComponent->setColour(GroupComponent::outlineColourId, Colour(0x66ffffff));
    groupComponent->setColour(GroupComponent::textColourId, Colours::white);

    addAndMakeVisible(table = new TableListBox("noadtable"));

    TableHeaderComponent* header = new TableHeaderComponent();
    header->addColumn("", SkoarpuscleDataModel::EColumn::field, 30);
    header->addColumn("", SkoarpuscleDataModel::EColumn::value, 300);
    header->setColour(ListBox::backgroundColourId, Colours::darkgrey);

    model = new SkoarpuscleDataModel(p);
    table->setHeader(header);
    table->setHeaderHeight(0);
    table->setModel(model);
    table->autoSizeAllColumns();

    setSize(330, 200);

}

SkoarpuscleTableComponent::~SkoarpuscleTableComponent() {
    model = nullptr;
    table = nullptr;
    groupComponent = nullptr;
}

void SkoarpuscleTableComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}


void SkoarpuscleTableComponent::resized()
{
    auto th = model->getNumRows() * table->getRowHeight();
    table->setBounds(20, 20, proportionOfWidth(1.0000f) - 34, th);

    groupComponent->setBounds(6, 0, proportionOfWidth(1.0000f) - 12, th + 39);

}
