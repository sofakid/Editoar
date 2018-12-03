#pragma once

#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "skoarpion.hpp"
#include "NoaditesListComponent.h"

class SkoarProjectionComponent :
    public Component
{
public:
    static SkoarProjectionComponent* getInstance ();
    SkoarProjectionComponent ();
    ~SkoarProjectionComponent ();

    void paint (Graphics&) override;
    void resized () override;

    void loadProjection (SkoarpionProjectionPtr p);

    void selectNoadite (const SkoarNoadite&);

private:
    std::unique_ptr<NoaditesListComponent> projectionComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarProjectionComponent)
};