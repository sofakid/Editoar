#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "SkoarTreeComponent.h"

class SkoarProjectionsComponent : public Component {
public:
    SkoarProjectionsComponent(ListOfSkoarpionProjectionsPtr);
    ~SkoarProjectionsComponent();

    void paint(Graphics& g) override;
    void resized() override;

private:

    ScopedPointer<TabbedComponent> tabby;

    ListOfSkoarpionProjectionsPtr projections;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarProjectionsComponent)

};