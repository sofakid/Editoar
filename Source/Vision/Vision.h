#pragma once
#include "FairyCursor.h"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "skoar_public.hpp"
#include "skoar.hpp"
#include "noad.hpp"


class Vision : public Component
{
public:
    CodeDocument& doc;
    SkoarCodeEditorComponent& editor;
    FairyCursor fairy;

    Vision (SkoarCodeEditorComponent& ed);
    virtual ~Vision () {};
    
    void anim_fairy_fly_to (const Rectangle<int>&);
    void fx_dim_rect (const Rectangle<int>&);

    void see_text_reset ();
    void see_text_highlight (const int offs, const int size);
    void see_fairy_fly_to (const size_t offs);

    void paint (Graphics& g) override;
    void resized () override;


private:
    
    std::list<Rectangle<int>> lit;
    std::list<Rectangle<int>> dim;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vision)
};

/*
template <typename T>
class TextRegionRectangles<T>
{
    Rectangle<T> top;
    Rectangle<T> middle;
    Rectangle<T> bottom;

    void fromText (SkoarCodeEditorComponent& editor, CodeDocument &doc) {
        T x = 0, y = 0, bottom = 0, right = 0, maxright = 0;
        // init top corner
        {
            CodeDocument::Position pos (doc, offs);
            auto rChar = editor.getCharacterBounds (pos);
            x = rChar.getX ();
            y = rChar.getY ();
            bottom = rChar.getBottom ();
            right = rChar.getRight ();
        }

        const auto n = offs + size;
        for (int i = offs; i < n; ++i)
        {
            CodeDocument::Position pos (doc, i);
            auto rChar = editor.getCharacterBounds (pos);

            auto rcX = rChar.getX ();
            auto rcY = rChar.getY ();
            auto rcBottom = rChar.getBottom ();
            auto rcRight = rChar.getRight ();
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
                {
                    bottom = rcBottom;
                }

                // next line, x is the the left.
                else if (rcX < x)
                {
                    top (x, y, maxright - x, bottom - y);
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
            auto rChar = editor.getCharacterBounds (pos);
            auto h = rChar.getHeight ();

            y = rChar.getY ();
            // end the block above
            middle (x, y - h, maxright - x, bottom - y - h);

            // add this line
            bottom = Rectangle<T>(x, y, right - x, bottom - y);

        }
    }
};

*/
