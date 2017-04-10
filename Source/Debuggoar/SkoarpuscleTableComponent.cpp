
#include "SkoarpuscleTableComponent.h"
#include "../Logging/SkoarLogger.hpp"


#define FUDGE_FACTOR 39
#define FUDGE_FACTOR_TRACTOR 12 
#define FUDGE_FACTOR_MOAR 50

SkoarpuscleTableComponent::SkoarpuscleTableComponent(SkoarpusclePtr p) :
    table(nullptr),
    model(nullptr)
{

    addAndMakeVisible(groupComponent = new GroupComponent("groupy", TRANS("Skoarpuscle")));
    groupComponent->setTextLabelPosition(Justification::centredLeft);
    groupComponent->setColour(GroupComponent::outlineColourId, Colour(0x66ffffff));
    groupComponent->setColour(GroupComponent::textColourId, Colours::white);


    if (p != nullptr) {
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
        
        int desired_width = 0;
        for (int i = 0; i < header->getNumColumns(true); ++i) {
            auto columnId = header->getColumnIdOfIndex(i, true);
            const int width = model != nullptr ? model->getColumnAutoSizeWidth(columnId) : 0;
            desired_width += width;
        }

        setSize(desired_width + FUDGE_FACTOR_MOAR, 500);
    }
    else {
        setSize(400, 500);
    }


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

int SkoarpuscleTableComponent::getHeightHint() {
    if (table != nullptr)
        return model->getNumRows() * table->getRowHeight() + FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;
    
    return FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;
}

int SkoarpuscleTableComponent::getWidthHint() {
    if (table != nullptr) {
        table->autoSizeAllColumns();
        int desired_width = 0;
        for (int i = 0; i < table->getHeader().getNumColumns(true); ++i) {
            auto columnId = table->getHeader().getColumnIdOfIndex(i, true);
            const int width = model != nullptr ? model->getColumnAutoSizeWidth(columnId) : 0;
            desired_width += width;
        }
        return desired_width + FUDGE_FACTOR_MOAR + FUDGE_FACTOR_TRACTOR;
    }
    return FUDGE_FACTOR_MOAR * 3;
}

Rectangle<int> SkoarpuscleTableComponent::getBoundsHint() {
    return Rectangle<int>(0, 0, getWidthHint(), getHeightHint());
}


void SkoarpuscleTableComponent::resized()
{
    auto r = getLocalBounds();
    if (table != nullptr)
        table->setBounds(20, 20, r.getWidth() - FUDGE_FACTOR, r.getHeight() - FUDGE_FACTOR - FUDGE_FACTOR_TRACTOR);

    groupComponent->setBounds(FUDGE_FACTOR_TRACTOR, 0, r.getWidth() - 2 * FUDGE_FACTOR_TRACTOR, r.getHeight() - FUDGE_FACTOR_TRACTOR);

}
#undef FUDGE_FACTOR_TRACTOR
#undef FUDGE_FACTOR
