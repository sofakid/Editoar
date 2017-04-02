#pragma once
#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarNoadDataModel.h"

class SkoarNoadTableComponent : public Component {
public:

    SkoarNoadTableComponent();
    ~SkoarNoadTableComponent();


    void paint(Graphics& g) override;
    void resized() override;

private:
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<TableListBox> table;
    ScopedPointer<SkoarNoadDataModel> model;
};