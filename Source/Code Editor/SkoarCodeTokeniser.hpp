#pragma once

#include "../Application/jucer_CommonHeaders.h"
#include "skoar_public.hpp"
#include "../Logging/SkoarLogger.hpp"

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
        SymbolColon,
        Duration,
        Cat,
        dynamic,
        
        msg,
        cthulhu,

        dal_goto,
        marker,
        deref,
        ottavas,
        
        listy,
        beat,
        conditional,
        skoarpion,
        loop,

        lute,
        meditation,
        ugen,
        arg_listy
	};

private:
	//==============================================================================
	JUCE_LEAK_DETECTOR(SkoarCodeTokeniser)
};
