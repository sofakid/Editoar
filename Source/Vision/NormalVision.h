#pragma once

#include "Vision.h"

class NormalVision : public Vision
{
public:
    NormalVision (SkoarCodeEditorComponent&);
    ~NormalVision () override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NormalVision)
};

