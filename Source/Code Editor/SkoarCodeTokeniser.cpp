

#include "../jucer_Headers.h"
#include "SkoarCodeTokeniser.hpp"
#include "../Application/jucer_Application.h"
#include "../Application/jucer_OpenDocumentManager.h"




//==============================================================================
SkoarCodeTokeniser::SkoarCodeTokeniser() {}
SkoarCodeTokeniser::~SkoarCodeTokeniser() {}

int SkoarCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
	source.skip();
    return 7;
}

CodeEditorComponent::ColourScheme SkoarCodeTokeniser::getDefaultColourScheme()
{
    struct Type
    {
        const char* name;
        uint32 colour;
    };

    const Type types[] =
    {
        { "Error",              0xffcc0000 },
        { "Comment",            0xff00aa00 },
        { "Keyword",            0xff0000cc },
        { "Operator",           0xff225500 },
        { "Identifier",         0xff000000 },
        { "Integer",            0xff880000 },
        { "Float",              0xff885500 },
        { "String",             0xff990099 },
        { "Bracket",            0xff000055 },
        { "Punctuation",        0xff004400 },
        { "Preprocessor Text",  0xff660000 }
    };

    CodeEditorComponent::ColourScheme cs;

    for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
        cs.set (types[i].name, Colour (types[i].colour));

    return cs;
}
