#include "VisionCanvas.h"
#include "../Application/jucer_AppearanceSettings.h"
#include "../Code Editor/SkoarCodeEditor.hpp"
#include "../Application/jucer_Application.h"

VisionCanvas::VisionCanvas (SkoarCodeEditorComponent* ed) :
    editor (*ed),
    doc (ed->getDocument ()),
    fairy (new FairyCursor (*ed)),
    cs (ed->getColourScheme ()),
    focusNoad (nullptr),
    focusNoadite (nullptr)
{
    setInterceptsMouseClicks (false, false);
    reload ();

    addAndMakeVisible (fairy);
    fairy->setAlwaysOnTop (true);

    setSize (200, 200);
}

void VisionCanvas::rebuildSegments ()
{
    if (skoar == nullptr)
        return;

    if (skoar->parsedOk == false)
    {
        rebuildFailedParseSegments ();
        return;
    }

    auto r = getLocalBounds ();
    segments.clearQuick (true);

    auto style = SkoarStyles::EStyle::nostyle;
    std::list<SkoarStyles::EStyle> styles { style };

    SkoarNoad::inorderBeforeAfter (skoar->tree,
        // before
        [&](SkoarNoadPtr p) {
            if (p->style != SkoarStyles::EStyle::nostyle)
                style = p->style;
            styles.push_back (style);

            if (p->size > 0)
            {
                int offs = p->offs > INT32_MAX ? 0 : static_cast<int> (p->offs);
                int size = p->size > INT32_MAX ? 0 : static_cast<int> (p->size);
                makeSegment (offs, size, style);
            }
        },
        // after
        [&](SkoarNoadPtr p) {
            styles.pop_back ();
            style = styles.back ();
        }
    );

    if (focusNoad != nullptr)
        focusOnNoad (focusNoad);

    else if (focusNoadite != nullptr)
        focusOnNoadite (*focusNoadite);
}

void VisionCanvas::rebuildFailedParseSegments ()
{
    SkoarString skoarce (doc.getAllContent ().toWideCharPointer ());
    auto r = getLocalBounds ();
    segments.clearQuick (true);
    
    wsmatch matches;
    wregex re_line (L".*");
    int offs = 0;
    wsregex_iterator it (skoarce.begin (), skoarce.end (), re_line);
    wsregex_iterator it_end;

    while (it != it_end)
    {
        auto match = *it;
        wstring line (match.str ());
        auto len (line.length ());
        int n (len > INT32_MAX ? 0 : static_cast<int>(len));
        if (n > 0)
            makeSegment (offs, n + 1, SkoarStyles::EStyle::nostyle);
        else
            n = 1;
        
        //skoarce = matches.suffix ().str ();
        offs += n;
        ++it;
    }
}

void VisionCanvas::makeSegment (int offs, int size, SkoarStyles::EStyle style) {
    CodeDocument::Position start (doc, offs);
    CodeDocument::Position end (doc, offs + size);

    auto r (getLocalBounds ());
    auto on_screen_r = editor.getCharacterBounds (start);
    if (on_screen_r.getY () < 0)
        return;

    if (on_screen_r.getBottom () > r.getBottom ())
        return;

    auto s = doc.getTextBetween (start, end);

    const wregex re_newline (L"[\\n]");
    if (regex_search (s.toWideCharPointer (), re_newline))
    {
        return;
    }

    auto seg = new VisionSegment (this, s, start, end);

    auto colour = cs.types.getUnchecked (SkoarStyles::to_int (style)).colour;
    seg->setColour (colour);

    addAndMakeVisible (seg);
    segments.add (seg);

    auto rStart = editor.getCharacterBounds (seg->start);
    auto rEnd = editor.getCharacterBounds (seg->end);

    auto x = rStart.getX ();
    auto y = rStart.getY ();
    auto w = rEnd.getRight () - x - rStart.getWidth ();
    auto h = rStart.getHeight ();

    seg->setBounds (x, y, w, h);
    seg->font = editor.getFont ();

}

void VisionCanvas::paint (Graphics& g) {
    //auto cs = editor.getColourScheme ();
    // todo: get background colour
    
    g.setColour (Colours::black);
    g.fillRect (getLocalBounds ());
}

void VisionCanvas::resized () {
}

void VisionCanvas::reload ()
{
    SkoarString skoarce (doc.getAllContent ().toWideCharPointer ());
    skoar = make_unique<SkoarLite> (skoarce, &SkoarLog);
    redraw ();
}

void VisionCanvas::redraw () {
    rebuildSegments ();
    highlightSelection ();
}

void VisionCanvas::highlightSelection () {
    if (editor.isHighlightActive ())
    {
        auto range (editor.getHighlightedRegion ());

        for (auto x : segments)
            x->select (range);
    }
    else
        for (auto x : segments)
            x->unselect ();

    repaint ();
}

FairyCursor* VisionCanvas::getFairy ()
{
    return fairy.get ();
}

void VisionCanvas::fly_fairy_to (CodeDocument::Position & pos)
{
    fairy->fly_to_pos (pos);
    highlightSelection ();
}

void VisionCanvas::showFairy ()
{
    fairy->showFairy ();
}

void VisionCanvas::hideFairy ()
{
    fairy->hideFairy ();
}

void VisionCanvas::focusOnNoad (SkoarNoadPtr p)
{
    focusNoad = p;
    focusNoadite = nullptr;

    if (focusNoad == nullptr)
        return;

    int offs (p->offs > INT32_MAX ? 0 : static_cast<int>(p->offs));
    size_t x (p->offs + p->size);

    int end (x > INT32_MAX ? offs : static_cast<int>(x));

    for (auto seg : segments)
        if (seg->start.getPosition () >= offs && seg->end.getPosition () <= end)
            seg->light ();
        else
            seg->dim ();

    CodeDocument::Position startPos (doc, offs);
    CodeDocument::Position endPos (doc, end);

    auto start_line = startPos.getLineNumber ();
    auto end_line = endPos.getLineNumber ();

    Range<int> scrollTo (start_line, end_line);
    editor.scrollToKeepLinesOnScreen (scrollTo);

    repaint ();
}


void VisionCanvas::focusOnNoadite (const SkoarNoadite& noadite)
{
    focusNoadite = &noadite;
    focusNoad = nullptr;

    int offs (noadite.offs > INT32_MAX ? 0 : static_cast<int>(noadite.offs));
    size_t x (noadite.offs + noadite.size);

    int end (x > INT32_MAX ? offs : static_cast<int>(x));

    for (auto seg : segments)
        if (seg->start.getPosition () >= offs && seg->end.getPosition () <= end)
            seg->light ();
        else
            seg->dim ();

    CodeDocument::Position startPos (doc, offs);
    CodeDocument::Position endPos (doc, end);

    auto start_line = startPos.getLineNumber ();
    auto end_line = endPos.getLineNumber ();

    Range<int> scrollTo (start_line, end_line);
    editor.scrollToKeepLinesOnScreen (scrollTo);

    repaint ();
}


void VisionCanvas::unfocusOnNoad ()
{
    focusNoad = nullptr;
    focusNoadite = nullptr;
}

void VisionCanvas::reloadColourScheme ()
{
    cs = editor.getColourScheme ();
    reload ();
}
