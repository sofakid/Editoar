#pragma once

#include "../jucer_Headers.h"
#include "SkoarpionComponent.h"
#include "skoar.hpp"

class SkoarpionsComponent : 
    public Component,
    public ComboBoxListener {
public:
    static SkoarpionsComponent* SkoarpionsComponent::getInstance();

    SkoarpionsComponent();
    ~SkoarpionsComponent();

    void paint(Graphics& g) override;
    void resized() override;

    void loadSkoar(Skoar *);

    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:
    
    const int combo_h;
    const int combo_pad;
    const int combo_pad_x2;
    const int combo_h_total;

    Array<SkoarpionPtr> skoarpions;
    ScopedPointer<SkoarpionComponent> skoarpionComponent;

    ScopedPointer<ComboBox> skoarpionsComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarpionsComponent)
};