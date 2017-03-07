/*
  ==============================================================================

    SkoarCodeTokenizer.h
    Created: 6 Mar 2017 10:51:26pm
    Author:  lucas

  ==============================================================================
*/

#ifndef SKOARCODETOKENIZER_H_INCLUDED
#define SKOARCODETOKENIZER_H_INCLUDED

class SkoarCodeTokeniser : public CodeTokeniser
{
public:
	//==============================================================================
	SkoarCodeTokeniser();
	~SkoarCodeTokeniser();

	//==============================================================================
	int readNextToken(CodeDocument::Iterator&) override;
	CodeEditorComponent::ColourScheme getDefaultColourScheme() override;

	/** The token values returned by this tokeniser. */
	enum TokenType
	{
		tokenType_error = 0,
		tokenType_comment,
		tokenType_keyword,
		tokenType_operator,
		tokenType_identifier,
		tokenType_integer,
		tokenType_float,
		tokenType_string,
		tokenType_bracket,
		tokenType_punctuation,
		tokenType_preprocessor
	};

private:
	//==============================================================================
	JUCE_LEAK_DETECTOR(SkoarCodeTokeniser)
};




#endif  // SKOARCODETOKENIZER_H_INCLUDED
