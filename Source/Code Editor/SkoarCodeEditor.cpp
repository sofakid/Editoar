#include "../jucer_Headers.h"
#include "SkoarCodeEditor.hpp"
#include "../Application/jucer_Application.h"
#include "../Application/jucer_OpenDocumentManager.h"

#include "../Logging/SkoarLogger.hpp"
#include "../Logging/SkoarLoggerComponent.h"

#include "../Vision/VisionCanvas.h" 
#include "../Debuggoar/DebuggoarComponent.h"


static SkoarCodeTokeniser skoarTokeniser;

SkoarCodeEditorComponent::SkoarCodeEditorComponent (const File& f, CodeDocument& doc) : 
    GenericCodeEditorComponent (f, doc, &skoarTokeniser), 
    docListener (doc, this),
    vision (nullptr)
{
    
    if (f == File ())
        return;

    vision = new VisionCanvas (this);
    doc.addListener (&docListener);
    setLineSpacing (1.3f);
    addAndMakeVisible (vision);

}

SkoarCodeEditorComponent::~SkoarCodeEditorComponent () {
    getDocument ().removeListener (&docListener);
    if (vision != nullptr)
        removeChildComponent (vision);
    vision = nullptr;
}

SkoarCodeTokeniser* SkoarCodeEditorComponent::getTokeniser () {
    return &skoarTokeniser;
}

void SkoarCodeEditorComponent::resized ()
{
    GenericCodeEditorComponent::resized ();

    auto r (getLocalBounds ());
    vision->setBounds (r);
    vision->redraw ();
}

void SkoarCodeEditorComponent::updateCaretPosition ()
{
    auto x (getCaretPos ());
    vision->fly_fairy_to (x);
}

void SkoarCodeEditorComponent::focusGained (FocusChangeType t)
{
    vision->showFairy ();
    CodeEditorComponent::focusGained (t);
}

void SkoarCodeEditorComponent::focusLost (FocusChangeType t)
{
    vision->hideFairy ();
    CodeEditorComponent::focusLost (t);
}

void SkoarCodeEditorComponent::focusOnNoad (SkoarNoadPtr p)
{
    vision->focusOnNoad (p);
}


void SkoarCodeEditorComponent::focusOnNoadite (const SkoarNoadite& noadite)
{
    vision->focusOnNoadite (noadite);
}

void SkoarCodeEditorComponent::resetVision ()
{
    vision->unfocusOnNoad ();
    vision->redraw ();
}


void SkoarCodeEditorComponent::reloadColourScheme ()
{
    vision->reloadColourScheme ();
}

void SkoarCodeEditorComponent::handleReturnKey ()
{
    GenericCodeEditorComponent::handleReturnKey ();

    CodeDocument::Position pos (getCaretPos ());

    String blockIndent, lastLineIndent;
    CodeHelpers::getIndentForCurrentBlock (pos, getTabString (getTabSize ()), blockIndent, lastLineIndent);

    const String remainderOfBrokenLine (pos.getLineText ());
    const int numLeadingWSChars = CodeHelpers::getLeadingWhitespace (remainderOfBrokenLine).length ();

    if (numLeadingWSChars > 0)
        getDocument ().deleteSection (pos, pos.movedBy (numLeadingWSChars));

    //if (remainderOfBrokenLine.trimStart ().startsWithChar ('}'))
    //    insertTextAtCaret (blockIndent);
    //else
        insertTextAtCaret (lastLineIndent);
    /*
    const String previousLine (pos.movedByLines (-1).getLineText ());
    const String trimmedPreviousLine (previousLine.trim ());

    if ((trimmedPreviousLine.startsWith ("if ")
        || trimmedPreviousLine.startsWith ("if(")
        || trimmedPreviousLine.startsWith ("for ")
        || trimmedPreviousLine.startsWith ("for(")
        || trimmedPreviousLine.startsWith ("while(")
        || trimmedPreviousLine.startsWith ("while "))
        && trimmedPreviousLine.endsWithChar (')'))
    {
        insertTabAtCaret ();
    }*/
}

void SkoarCodeEditorComponent::insertTextAtCaret (const String& newText)
{
    if (getHighlightedRegion ().isEmpty ())
    {
        const CodeDocument::Position pos (getCaretPos ());

        if ((newText == "{" || newText == "}")
            && pos.getLineNumber () > 0
            && pos.getLineText ().trim ().isEmpty ())
        {
            moveCaretToStartOfLine (true);

            String blockIndent, lastLineIndent;
            if (CodeHelpers::getIndentForCurrentBlock (pos, getTabString (getTabSize ()), blockIndent, lastLineIndent))
            {
                GenericCodeEditorComponent::insertTextAtCaret (blockIndent);

                if (newText == "{")
                    insertTabAtCaret ();
            }
        }
    }

    GenericCodeEditorComponent::insertTextAtCaret (newText);

}

void SkoarCodeEditorComponent::addPopupMenuItems (PopupMenu& menu, const MouseEvent* e)
{
    GenericCodeEditorComponent::addPopupMenuItems (menu, e);
}

void SkoarCodeEditorComponent::performPopupMenuAction (int menuItemID)
{
    GenericCodeEditorComponent::performPopupMenuAction (menuItemID);
}

// ------------------------------------------------------------------------------
SkoarCodeEditorComponent::DocumentListener::DocumentListener (CodeDocument& document, SkoarCodeEditorComponent* ed) : 
    doc (document),
    editor (ed)
    {}
SkoarCodeEditorComponent::DocumentListener::~DocumentListener () {}

/** Called by a CodeDocument when text is added. */
void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextInserted (const String& /*newText*/, int /*insertIndex*/) {
    editor->vision->reload ();
    MessageManager::callAsync ([&]() {
        auto debuggoar (DebuggoarComponent::getDebuggoar ());
        if (debuggoar == nullptr)
            return;

        const MessageManagerLock mmLock;
        debuggoar->reloadSkoar ();
    });
}

/** Called by a CodeDocument when text is deleted. */
void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextDeleted (int /*startIndex*/, int /*endIndex*/) {
    editor->vision->reload ();
    MessageManager::callAsync ([&]() {
        auto debuggoar (DebuggoarComponent::getDebuggoar ());
        if (debuggoar == nullptr)
            return;

        const MessageManagerLock mmLock;
        debuggoar->reloadSkoar ();
    });
}


// ------------------------------------------------------------------------------

void SkoarCodeEditorComponent::editorViewportPositionChanged ()
{
    GenericCodeEditorComponent::editorViewportPositionChanged ();
    vision->redraw ();
}