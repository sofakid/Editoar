
#ifndef SKOARCODEEDITOR_HPP_INCLUDED
#define SKOARCODEEDITOR_HPP_INCLUDED

#include "../Project/jucer_Project.h"
#include "../Application/jucer_DocumentEditorComponent.h"
#include "jucer_SourceCodeEditor.h"
#include "SkoarCodeTokeniser.hpp"

class SkoarCodeEditorComponent : public GenericCodeEditorComponent
{
public:
	SkoarCodeEditorComponent(const File&, CodeDocument&);
	~SkoarCodeEditorComponent();

	void addPopupMenuItems(PopupMenu&, const MouseEvent*) override;
	void performPopupMenuAction(int menuItemID) override;

	void handleReturnKey() override;
	void insertTextAtCaret(const String& newText) override;

	class DocumentListener : public CodeDocument::Listener
	{
	public:
		DocumentListener(CodeDocument& document);
		~DocumentListener() override;

		/** Called by a CodeDocument when text is added. */
		void codeDocumentTextInserted(const String& newText, int insertIndex) override;

		/** Called by a CodeDocument when text is deleted. */
		void codeDocumentTextDeleted(int startIndex, int endIndex) override;

	private:
		CodeDocument& doc;
        SkoarCodeEditorComponent *ed;
	};
private:
	void insertComponentClass();

	DocumentListener docListener;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarCodeEditorComponent)
};


#endif  // SKOARCODEEDITOR_HPP_INCLUDED
