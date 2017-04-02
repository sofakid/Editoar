#pragma once
#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarpuscleDataModel.h"

class SkoarpuscleTableComponent : public Component {
public:

    SkoarpuscleTableComponent();
    ~SkoarpuscleTableComponent();


    void paint(Graphics& g) override;
    void resized() override;

private:
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<TableListBox> table;
    ScopedPointer<SkoarpuscleDataModel> model;
};