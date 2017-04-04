#include "SkoarNoadTableComponent.h"
#include "../Logging/SkoarLogger.hpp"

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

void SkoarNoadTableComponent::resized()
{
    auto th = model->getNumRows() * table->getRowHeight();
    table->setBounds(20, 20, proportionOfWidth(1.0000f) - 34, th);
    
    groupComponent->setBounds(6, 0, proportionOfWidth(1.0000f) - 12, th + 39);

}
