#include "DeetsTableComponent.h"

#define FUDGE_FACTOR 39
#define FUDGE_FACTOR_TRACTOR 12 
#define FUDGE_FACTOR_MOAR 50

DeetsTableComponent::DeetsTableComponent(
    String label,
    TableListBoxModel* dataModel) :
    table(nullptr),
    model(dataModel)
{
    addAndMakeVisible(groupComponent = new GroupComponent("groupy", label));
    groupComponent->setTextLabelPosition(Justification::centredLeft);
    groupComponent->setColour(GroupComponent::outlineColourId, Colour(0x66ffffff));
    groupComponent->setColour(GroupComponent::textColourId, Colours::white);

    addAndMakeVisible(table = new TableListBox());

    TableHeaderComponent* header = new TableHeaderComponent();
    header->addColumn("", EColumn::field, 30);
    header->addColumn("", EColumn::value, 300);
    header->setColour(ListBox::backgroundColourId, Colours::darkgrey);

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

    auto& scrollbar (table->getVerticalScrollBar());
    scrollbar.setColour(ScrollBar::ColourIds::thumbColourId, Colours::darkgrey);
    scrollbar.setColour(ScrollBar::ColourIds::trackColourId, Colours::black);
    scrollbar.setColour(ScrollBar::ColourIds::backgroundColourId, Colours::black);

    table->setColour(ListBox::ColourIds::backgroundColourId, Colours::black);

    setSize(desired_width + FUDGE_FACTOR_MOAR, 500);

}

DeetsTableComponent::~DeetsTableComponent() {
    model = nullptr;
    table = nullptr;
    groupComponent = nullptr;
}

void DeetsTableComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

int DeetsTableComponent::getHeightHint() {
    if (table != nullptr)
        return model->getNumRows() * table->getRowHeight() + FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;

    return FUDGE_FACTOR + FUDGE_FACTOR_TRACTOR;
}

int DeetsTableComponent::getWidthHint() {
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

Rectangle<int> DeetsTableComponent::getBoundsHint() {
    return Rectangle<int>(0, 0, getWidthHint(), getHeightHint());
}


void DeetsTableComponent::resized()
{
    auto r = getLocalBounds();
    if (table != nullptr)
        table->setBounds(20, 20, r.getWidth() - FUDGE_FACTOR, r.getHeight() - FUDGE_FACTOR - FUDGE_FACTOR_TRACTOR);

    groupComponent->setBounds(FUDGE_FACTOR_TRACTOR, 0, r.getWidth() - 2 * FUDGE_FACTOR_TRACTOR, r.getHeight() - FUDGE_FACTOR_TRACTOR);

}
#undef FUDGE_FACTOR_TRACTOR
#undef FUDGE_FACTOR
