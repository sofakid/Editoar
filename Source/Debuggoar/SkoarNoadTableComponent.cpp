#include "SkoarNoadTableComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "SkoarNoadDataModel.h"
#include "DebuggoarComponent.h"

#define FUDGE_FACTOR 39
#define FUDGE_FACTOR_TRACTOR 12 
#define FUDGE_FACTOR_MOAR 50 


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

    int desired_width = 0;
    for (int i = 0; i < header->getNumColumns(true); ++i) {
        auto columnId = header->getColumnIdOfIndex(i, true);
        const int width = model != nullptr ? model->getColumnAutoSizeWidth(columnId) : 0;
        desired_width += width;
    }

    setSize(desired_width + FUDGE_FACTOR_MOAR, 500);
}

SkoarNoadTableComponent::~SkoarNoadTableComponent() {
    noad = nullptr;
}

void SkoarNoadTableComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}


int SkoarNoadTableComponent::getHeightHint() {
    return model->getNumRows() * table->getRowHeight() + FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;
}

int SkoarNoadTableComponent::getWidthHint() {
    int desired_width = 0;
    for (int i = 0; i < table->getHeader().getNumColumns(true); ++i) {
        auto columnId = table->getHeader().getColumnIdOfIndex(i, true);
        const int width = model != nullptr ? model->getColumnAutoSizeWidth(columnId) : 0;
        desired_width += width;
    }
    return desired_width + FUDGE_FACTOR_MOAR + FUDGE_FACTOR_TRACTOR;
}

Rectangle<int> SkoarNoadTableComponent::getBoundsHint() {
    return Rectangle<int>(0, 0, getWidthHint(), getHeightHint());
}

void SkoarNoadTableComponent::resized()
{
    auto r = getLocalBounds();
    table->setBounds(20, 20, r.getWidth() - FUDGE_FACTOR, r.getHeight() - FUDGE_FACTOR - FUDGE_FACTOR_TRACTOR);
    
    groupComponent->setBounds(FUDGE_FACTOR_TRACTOR, 0, r.getWidth() - 2 * FUDGE_FACTOR_TRACTOR, r.getHeight() - FUDGE_FACTOR_TRACTOR);
}
#undef FUDGE_FACTOR_TRACTOR
#undef FUDGE_FACTOR

