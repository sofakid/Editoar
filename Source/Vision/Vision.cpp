#include "Vision.h"

Vision::Vision (SkoarCodeEditorComponent& ed) :
    editor(ed),
    doc(ed.getDocument()),
    fairy(ed)
{
    setAlwaysOnTop (true);
}

void Vision::anim_fairy_fly_to (const Rectangle<int>&)
{
    // animate the fairy to r.getX() r.getY()
}

void Vision::fx_dim_rect (const Rectangle<int>&)
{
}

void Vision::see_text_reset ()
{
    lit.clear ();
    dim.clear ();
}

// this road seems terrible.
void Vision::see_text_highlight (const int offs, const int size)
{
    int x (0), y (0), bottom (0), right (0), maxright (0);

    // init top corner
    {
        CodeDocument::Position pos (doc, offs);
        auto rChar (editor.getCharacterBounds (pos));
        x = rChar.getX ();
        y = rChar.getY ();
        bottom = rChar.getBottom ();
        right = rChar.getRight ();
    }

    const auto n (offs + size);
    for (int i = offs; i < n; ++i)
    {
        CodeDocument::Position pos (doc, i);
        auto rChar (editor.getCharacterBounds (pos));
        auto rcX (rChar.getX ());
        auto rcY (rChar.getY ());
        auto rcBottom (rChar.getBottom ());
        auto rcRight (rChar.getRight ());

        // same line?
        if (rcBottom == bottom)
        {
            maxright = std::max (right, rcRight);
            right = rcRight;
        }
        else
        {
            // next line but same left edge
            if (rcX == x)
                bottom = rcBottom;

            // next line, x is the the left.
            else if (rcX < x) 
            {
                lit.emplace_back (x, y, maxright - x, bottom - y );
                x = rcX;
                y = rcY;
                bottom = rcBottom;
                right = rcRight;
                maxright = right;
            }

            // next line, but x is to the right?
            else
            {
                // ???
            }

        }
    }

    // we are on the final line, and we need to end to the left of the line above.
    if (right < maxright)
    {
        CodeDocument::Position pos (doc, offs + size);
        auto rChar (editor.getCharacterBounds (pos));
        auto h (rChar.getHeight ());
        
        y = rChar.getY ();
        // end the block above
        lit.emplace_back (x, y - h, maxright - x, bottom - y - h);

        // add this line
        lit.emplace_back (x, y, right - x, bottom - y);

    }
}

void Vision::see_fairy_fly_to (const size_t offs)
{
    fairy.fly_to_offs (offs);
}

void Vision::paint (Graphics &)
{
}

void Vision::resized ()
{
}
