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
        SymbolColon,
        Duration,
        Cat,
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
        loop,

        lute,
        meditation,
        ugen,
        arg_listy,

        // inactives
        False_inactive,
        True_inactive,
        Times_inactive,
        Choard_inactive,
        Symbol_inactive,
        Comment_inactive,
        MathOp_inactive,
        BooleanOp_inactive,
        HashLevel_inactive,
        Bars_inactive,
        AssOp_inactive,
        Carrot_inactive,
        Voice_inactive,
        Fairy_inactive,
        Freq_inactive,
        String_inactive,
        NamedNoat_inactive,
        MsgOp_inactive,
        Tuplet_inactive,
        Int_inactive,
        Float_inactive,

        SymbolColon_inactive,
        Duration_inactive,
        Cat_inactive,

        dynamic_inactive,
        msg_inactive,
        cthulhu_inactive,
        marker_inactive,
        deref_inactive,
        ottavas_inactive,
        listy_inactive,
        beat_inactive,
        conditional_inactive,
        skoarpion_inactive,
        loop_inactive,

        lute_inactive,
        meditation_inactive,
        ugen_inactive,
        arg_listy_inactive

	};

    const int num_regular_styles = 39;

    CodeDocument *doc;
    void setDoc(CodeDocument *document);

    void parseSkoarAndPrepareStyles(CodeDocument &source);

    void growStyles(int start, int end);
    void shrinkStyles(int start, int end);

    void activate_range(size_t offs, size_t size);

private:
	//==============================================================================
    //SkoarNoadPtr lastTree;

    Array<SkoarStyles::EStyle> styles;

	JUCE_LEAK_DETECTOR(SkoarCodeTokeniser)
};
