#pragma once

#include "../jucer_Headers.h"
#include "SkoarpionComponent.h"
#include "skoar.hpp"

class DebuggoarDeets : public Component {
public:
    DebuggoarDeets();
    ~DebuggoarDeets();

    void paint(Graphics& g) override;
    void resized() override;

    void loadSkoar(Skoar *);

private:
    ScopedPointer<TabbedComponent> skoarpionsTabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DebuggoarDeets)
};