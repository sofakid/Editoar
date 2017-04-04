#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "skoarpion.hpp"
#include "SkoarProjectionsComponent.h"

class SkoarpionComponent : public Component {
public:
    SkoarpionComponent(SkoarpionPtr);
    ~SkoarpionComponent();
    
    void paint(Graphics& g) override;
    void resized() override;

private:
    ScopedPointer<SkoarProjectionsComponent> projections;
    SkoarpionPtr skoarpion;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarpionComponent)
};