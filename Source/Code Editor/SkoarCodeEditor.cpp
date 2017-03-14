


#include "../jucer_Headers.h"
#include "SkoarCodeEditor.hpp"
#include "../Application/jucer_Application.h"
#include "../Application/jucer_OpenDocumentManager.h"

#include "../Logging/SkoarLogger.hpp"
#include "../Logging/SkoarLoggerComponent.h"

static SkoarCodeTokeniser skoarTokeniser;

SkoarCodeEditorComponent::SkoarCodeEditorComponent(const File& f, CodeDocument& doc)
	: GenericCodeEditorComponent(f, doc, &skoarTokeniser), docListener(doc)
{
	doc.addListener(&docListener);

    setLineSpacing(1.3f);
    skoarTokeniser.setDoc(&doc);
    skoarTokeniser.parseSkoarAndPrepareStyles(doc);
}

SkoarCodeEditorComponent::~SkoarCodeEditorComponent() {
	getDocument().removeListener(&docListener);
}

void SkoarCodeEditorComponent::handleReturnKey()
{
	GenericCodeEditorComponent::handleReturnKey();

	CodeDocument::Position pos(getCaretPos());

	String blockIndent, lastLineIndent;
	CodeHelpers::getIndentForCurrentBlock(pos, getTabString(getTabSize()), blockIndent, lastLineIndent);

	const String remainderOfBrokenLine(pos.getLineText());
	const int numLeadingWSChars = CodeHelpers::getLeadingWhitespace(remainderOfBrokenLine).length();

	if (numLeadingWSChars > 0)
		getDocument().deleteSection(pos, pos.movedBy(numLeadingWSChars));

	if (remainderOfBrokenLine.trimStart().startsWithChar('}'))
		insertTextAtCaret(blockIndent);
	else
		insertTextAtCaret(lastLineIndent);

	const String previousLine(pos.movedByLines(-1).getLineText());
	const String trimmedPreviousLine(previousLine.trim());

	if ((trimmedPreviousLine.startsWith("if ")
		|| trimmedPreviousLine.startsWith("if(")
		|| trimmedPreviousLine.startsWith("for ")
		|| trimmedPreviousLine.startsWith("for(")
		|| trimmedPreviousLine.startsWith("while(")
		|| trimmedPreviousLine.startsWith("while "))
		&& trimmedPreviousLine.endsWithChar(')'))
	{
		insertTabAtCaret();
	}
}

void SkoarCodeEditorComponent::insertTextAtCaret(const String& newText)
{
	if (getHighlightedRegion().isEmpty())
	{
		const CodeDocument::Position pos(getCaretPos());

		if ((newText == "{" || newText == "}")
			&& pos.getLineNumber() > 0
			&& pos.getLineText().trim().isEmpty())
		{
			moveCaretToStartOfLine(true);

			String blockIndent, lastLineIndent;
			if (CodeHelpers::getIndentForCurrentBlock(pos, getTabString(getTabSize()), blockIndent, lastLineIndent))
			{
				GenericCodeEditorComponent::insertTextAtCaret(blockIndent);

				if (newText == "{")
					insertTabAtCaret();
			}
		}
	}

	GenericCodeEditorComponent::insertTextAtCaret(newText);
}

void SkoarCodeEditorComponent::addPopupMenuItems(PopupMenu& menu, const MouseEvent* e)
{
	GenericCodeEditorComponent::addPopupMenuItems(menu, e);

	//menu.addSeparator();
	//menu.addItem(insertComponentID, TRANS("Insert code for a new Component class..."));
}

void SkoarCodeEditorComponent::performPopupMenuAction(int menuItemID)
{
	//if (menuItemID == insertComponentID)
	//	insertComponentClass();

	GenericCodeEditorComponent::performPopupMenuAction(menuItemID);
}

void SkoarCodeEditorComponent::insertComponentClass()
{
	AlertWindow aw(TRANS("Insert a new C++ class"),
		TRANS("Please enter a name for the new class"),
		AlertWindow::NoIcon, nullptr);

	const char* classNameField = "Class Name";

	aw.addTextEditor(classNameField, String(), String(), false);
	aw.addButton(TRANS("Insert Code"), 1, KeyPress(KeyPress::returnKey));
	aw.addButton(TRANS("Cancel"), 0, KeyPress(KeyPress::escapeKey));

	while (aw.runModalLoop() != 0)
	{
		const String className(aw.getTextEditorContents(classNameField).trim());

		if (className == CodeHelpers::makeValidIdentifier(className, false, true, false))
		{
			String code(BinaryData::jucer_NewCppFileTemplate_cpp);
			code = code.replace("COMPONENTCLASS", className);

			insertTextAtCaret(code);
			break;
		}
	}
}



// ------------------------------------------------------------------------------
SkoarCodeEditorComponent::DocumentListener::DocumentListener(CodeDocument& document) : doc(document) {}
SkoarCodeEditorComponent::DocumentListener::~DocumentListener() {}

/** Called by a CodeDocument when text is added. */
//void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextInserted(const String& newText, int insertIndex)
void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextInserted(const String&, int) {
    skoarTokeniser.parseSkoarAndPrepareStyles(doc);
}

/** Called by a CodeDocument when text is deleted. */
//void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextDeleted(int startIndex, int endIndex)
void SkoarCodeEditorComponent::DocumentListener::codeDocumentTextDeleted(int, int) {
    skoarTokeniser.parseSkoarAndPrepareStyles(doc);
}
