#pragma once
#include "Vision.h"

class DebuggoarVision : public Vision
{
public:
    DebuggoarVision (SkoarCodeEditorComponent&);
    ~DebuggoarVision () override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebuggoarVision)

};