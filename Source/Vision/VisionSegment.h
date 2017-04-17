#pragma once
#include "../jucer_Headers.h"

class VisionCanvas;

class VisionSegment : public Component
{
public:
    CodeDocument::Position start;
    CodeDocument::Position end;
    String text;
    const int length;
    const float flength;
    float sel_start_ratio;
    float sel_end_ratio;

    Colour colour;
    Colour background;
    Colour calculated_colour;
    Colour calculated_background;
    Font font;
    VisionCanvas* canvas;

    int selectionStart;
    int selectionEnd;


    bool isDim;
    bool isSelected;
    bool isPartiallySelected;

    VisionSegment (VisionCanvas *vision_canvas, String txt, CodeDocument::Position s, CodeDocument::Position e);
    ~VisionSegment ();

    void setColour (Colour &col);
    void dim ();
    void light ();

    void calculate_colour ();

    void select (Range<int> range);

    void unselect ();

    void paint (Graphics&g) override;

};