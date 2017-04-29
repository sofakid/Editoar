
#ifndef SKOARCODEEDITOR_HPP_INCLUDED
#define SKOARCODEEDITOR_HPP_INCLUDED

#include "../Project/jucer_Project.h"
#include "../Application/jucer_DocumentEditorComponent.h"
#include "jucer_SourceCodeEditor.h"
#include "SkoarCodeTokeniser.hpp"
#include "../Utility/jucer_EditoarLookAndFeel.h"
#include "../Vision/VisionCanvas.h"

class SkoarCodeEditorComponent : public GenericCodeEditorComponent
{
public:

	SkoarCodeEditorComponent(const File&, CodeDocument&);
	~SkoarCodeEditorComponent();

	void addPopupMenuItems(PopupMenu&, const MouseEvent*) override;
	void performPopupMenuAction(int menuItemID) override;

    void editorViewportPositionChanged () override;

	void handleReturnKey() override;
	void insertTextAtCaret(const String& newText) override;

	class DocumentListener : public CodeDocument::Listener
	{
	public:
		DocumentListener(CodeDocument& document, SkoarCodeEditorComponent* ed);
		~DocumentListener() override;

		/** Called by a CodeDocument when text is added. */
		void codeDocumentTextInserted(const String& newText, int insertIndex) override;

		/** Called by a CodeDocument when text is deleted. */
		void codeDocumentTextDeleted(int startIndex, int endIndex) override;

	private:
		CodeDocument& doc;
        SkoarCodeEditorComponent* editor;
	};

    SkoarCodeTokeniser* getTokeniser();

    void resized () override;
    void paint (Graphics&) override {};

    void updateCaretPosition () override;

    void focusGained (FocusChangeType) override;
    void focusLost (FocusChangeType) override;

    void focusOnNoad (SkoarNoadPtr p);
    void focusOnNoadite (const SkoarNoadite & noadite);

    void resetVision ();

    void reloadColourScheme ();

private:
	DocumentListener docListener;
    ScopedPointer<VisionCanvas> vision;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarCodeEditorComponent)
};


#endif  // SKOARCODEEDITOR_HPP_INCLUDED
