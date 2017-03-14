/*
  ==============================================================================

    SkoarCodeTokenizer.h
    Created: 6 Mar 2017 10:51:26pm
    Author:  lucas

  ==============================================================================
*/

#ifndef SKOARCODETOKENIZER_H_INCLUDED
#define SKOARCODETOKENIZER_H_INCLUDED

#include "../Application/jucer_CommonHeaders.h"
#include "skoar_public.hpp"

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
        nostyle = 0,
        parseFail,

        False,        
        True,
        Times,
        Choard,
        Symbol,
        Comment,
        MathOp,
        BooleanOp,
        HashLevel,
        Bars,
        AssOp,
        Carrot,
        Voice,
        Fairy,
        Freq,
        String,
        NamedNoat,
        MsgOp,
        Tuplet,
        Int,
        Float,
        
        //SymbolColon,
        //Duration,
        //Cat,

        dynamic,
        msg,
        cthulhu,
        marker,
        deref,
        ottavas,
        listy,
        beat,
        conditional,
        skoarpion,
        loop

        //lute,
        //meditation,
        //ugen,
        //arg_listy

	};

    CodeDocument *doc;
    void setDoc(CodeDocument *document);

    void parseSkoarAndPrepareStyles(CodeDocument &source);
private:
	//==============================================================================
    //SkoarNoadPtr lastTree;

    Array<SkoarStyles::EStyle> styles;

	JUCE_LEAK_DETECTOR(SkoarCodeTokeniser)
};

#endif  // SKOARCODETOKENIZER_H_INCLUDED
