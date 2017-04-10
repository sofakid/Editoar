#pragma once
#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarpuscleDataModel.h"
#include "all_skoarpuscles.hpp"


class DeetsTableComponent : public Component {
public:
    enum EColumn {
        field = 1,
        value
    };

    DeetsTableComponent(String label, TableListBoxModel* dataModel);
    ~DeetsTableComponent() override;

    void paint(Graphics& g) override;
    void resized() override;

    int getHeightHint();
    int getWidthHint();
    Rectangle<int> getBoundsHint();

    ScopedPointer<TableListBox> table;
    ScopedPointer<TableListBoxModel> model;

private:
    ScopedPointer<GroupComponent> groupComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeetsTableComponent)

};
