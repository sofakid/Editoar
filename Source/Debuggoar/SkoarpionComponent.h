#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "skoarpion.hpp"
#include "NoaditesListComponent.h"

class SkoarpionComponent :
    public Component,
    public ComboBox::Listener
{
public:
    SkoarpionComponent (SkoarpionPtr);
    ~SkoarpionComponent ();

    void paint (Graphics&) override;
    void resized () override;

    void comboBoxChanged (ComboBox*) override;

    void selectNoad (SkoarNoad*);
    void selectNoadite (const SkoarNoadite&);
    void selectVoice (String);

private:

    const int combo_h;
    const int combo_pad;
    const int combo_pad_x2;
    const int combo_h_total;

    Array<SkoarpionProjectionPtr> projections;
    ScopedPointer<NoaditesListComponent> projectionComponent;

    ScopedPointer<ComboBox> projectionsComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarpionComponent)
};