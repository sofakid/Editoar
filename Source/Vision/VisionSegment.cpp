#include "VisionSegment.h"
#include "VisionCanvas.h"

VisionSegment::VisionSegment (VisionCanvas* vision_canvas, String txt, CodeDocument::Position s, CodeDocument::Position e) :
    canvas (vision_canvas),
    text (txt),
    length (txt.length()),
    flength (static_cast<float>(txt.length ())),
    sel_start_ratio (0.0f),
    sel_end_ratio (0.0f),
    start (s),
    end (e),
    colour (Colours::white),
    background (Colours::black),
    calculated_colour (Colours::white),
    calculated_background (Colours::black),
    font (),
    isDim (false),
    isSelected (false),
    isPartiallySelected (false),
    selectionStart(0),
    selectionEnd(0)
{
    
    setPaintingIsUnclipped (true);

}

VisionSegment::~VisionSegment ()
{
    //canvas->removeChildComponent (this);
}

void VisionSegment::setColour (Colour & col)
{
    colour = col;
    calculate_colour ();
}

void VisionSegment::dim ()
{
    isDim = true;
    calculate_colour ();
}

void VisionSegment::light ()
{
    isDim = false;
    calculate_colour ();
}

void VisionSegment::calculate_colour ()
{
    calculated_colour = colour;
    if (isDim)
    {
        calculated_colour = calculated_colour.withAlpha (0.4f);
    }

    calculated_background = isSelected ? Colours::darkblue.darker(0.7f) : background;

}

void VisionSegment::select (Range<int> range)
{
    int offs = start.getPosition ();
    Range<int> us (offs, end.getPosition ());
    Range<int> intersection = range.getIntersectionWith (us);

    auto intersection_length = intersection.getLength ();
    isSelected = (intersection_length > 0);
    if (isSelected)
    {
        if (intersection_length < length)
        {
            selectionStart = intersection.getStart ();
            selectionEnd = intersection.getEnd ();

            auto sel_start_i = selectionStart - start.getPosition ();
            auto sel_end_i = selectionEnd - start.getPosition ();

            sel_start_ratio = static_cast<float>(sel_start_i) / flength;
            sel_end_ratio = static_cast<float>(sel_end_i) / flength;

            isPartiallySelected = true;
        }
        else 
            isPartiallySelected = false;

    }
    else
        isPartiallySelected = false;

    calculate_colour ();
}


void VisionSegment::unselect ()
{
    isSelected = false;
    calculate_colour ();
}

void VisionSegment::paint (Graphics & g)
{
    auto r (getLocalBounds ());

    if (isPartiallySelected)
    {
        // fill with background
        g.setColour (background);
        g.fillRect (r);

        float seg_length = static_cast<float>(r.getWidth ());

        float x = seg_length * sel_start_ratio;
        float x_end = seg_length * sel_end_ratio;
        float y = 0.0f;
        float w = x_end - x;
        float h = static_cast<float>(r.getHeight ());
        g.setColour (calculated_background);
        g.fillRect (x, y, w, h);
    }
    else
    {
        g.setColour (calculated_background);
        g.fillRect (r);
    }
    g.setColour (calculated_colour);
    g.setFont (font);
    g.drawText (text, r, Justification::right, 1);
}