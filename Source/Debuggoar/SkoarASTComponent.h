#pragma once

#include "../jucer_Headers.h"
#include "SkoarTreeComponent.h"
#include "skoar.hpp"

class SkoarASTComponent :
    public Component
{
public:
    static SkoarASTComponent* SkoarASTComponent::getInstance ();

    SkoarASTComponent ();
    ~SkoarASTComponent ();

    void paint (Graphics&) override;
    void resized () override;

    void loadSkoarpion (SkoarpionPtr skoarpion);
    void selectNoad (SkoarNoad*);

private:
    ScopedPointer<SkoarTreeComponent> skoarpionComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarASTComponent)
};