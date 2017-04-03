#pragma once
#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarpuscleDataModel.h"
#include "all_skoarpuscles.hpp"

class SkoarpuscleTableComponent : public Component {
public:

    SkoarpuscleTableComponent(SkoarpusclePtr p);
    ~SkoarpuscleTableComponent();


    void paint(Graphics& g) override;
    void resized() override;

private:
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<TableListBox> table;
    ScopedPointer<SkoarpuscleDataModel> model;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarpuscleTableComponent)

};