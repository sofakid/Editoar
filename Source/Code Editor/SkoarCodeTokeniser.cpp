

#include "../jucer_Headers.h"
#include "SkoarCodeTokeniser.hpp"
#include "../Application/jucer_Application.h"
#include "../Application/jucer_OpenDocumentManager.h"

//==============================================================================
SkoarCodeTokeniser::SkoarCodeTokeniser() :
    //lastTree(nullptr),
    doc(nullptr)
{}

SkoarCodeTokeniser::~SkoarCodeTokeniser() {
    //lastTree = nullptr; // do we delete?
    doc = nullptr;
}

int SkoarCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
   
    if (source.isEOF()) {
        return 0;
    }
    auto pos = source.getPosition();
    if (styles.size() <= pos) {
        SkoarLog.e("Styles underflow", "styles.size()", styles.size(), "pos", pos);
        return 0;
    }
    source.skip();
    return static_cast<std::underlying_type<SkoarStyles::EStyle>::type>(styles.getUnchecked(pos));
}

void SkoarCodeTokeniser::setDoc(CodeDocument *document) {
    doc = document;
};


CodeEditorComponent::ColourScheme SkoarCodeTokeniser::getDefaultColourScheme()
{
    struct Type
    {
        const char* name;
        Colour colour;
    };

    const Type types[] =
    {
        { "nostyle", Colour( 0xffffffff ) },
        { "parseFail", Colour( 0xffCC2222 ) },


        { "False",  Colour ( 0xffFFF82E ) },
        { "True",  Colour ( 0xffFFF82E ) },
        { "Times",  Colour ( 0xffFFF82E ) },
        { "Choard",  Colour ( 0xff1EFA67 ) },

        { "Symbol",  Colour ( 0xffEEEECC ) },
        { "Comment",  Colour ( 0xffE5E5B5 ) },
        { "MathOp",  Colour ( 0xffB340B1 ) },
        { "BooleanOp",  Colour ( 0xffB340B1 ) },
        

        { "HashLevel",  Colour ( 0xffFFF82E ) },
        { "Bars",  Colour ( 0xff9DB562 ) },
        { "AssOp",  Colour ( 0xffB340B1 ) },
        { "Carrot",  Colour ( 0xffB340B1 ) },
        
        { "Voice",  Colour ( 0xff0B6BD9 ) },
        { "Fairy",  Colour ( 0xffFF99FF ) },
        { "Freq",  Colour ( 0xffFFF82E ) },
        { "String",  Colour ( 0xffB58962 ) },
        



        { "NamedNoat",  Colour ( 0xff1EFA67 ) },
        { "MsgOp",  Colour ( 0xffB340B1 ) },
        { "Tuplet",  Colour ( 0xffB340B1 ) },
        { "Int",  Colour ( 0xffFFF82E ) },
        
        { "Float",  Colour ( 0xffFFF82E ) },

        //{ "SymbolColon",  Colour ( 0xffEEEECC ) },
        //{ "Duration",  Colour ( 0xffF8FF2E ) },
        //{ "Cat",  Colour ( 0xffFFF82E ) },

        { "dynamic",  Colour ( 0xff998877 ) },
        { "msg",  Colour ( 0xff888888 ) },
        { "cthulhu",  Colour ( 0xffFF2E2E ) },
        

        { "marker",  Colour ( 0xffCCDDFF ) },
        { "deref",  Colour ( 0xffB340B1 ) },
        { "ottavas",  Colour ( 0xff999999 ) },
        { "listy",  Colour ( 0xff6699EE ) },
        
        { "beat",  Colour ( 0xff1EB1FA ) },
        { "conditional",  Colour ( 0xffB59D62 ) },
        { "skoarpion",  Colour ( 0xff9DB562 ) },
        { "loop",  Colour ( 0xff77EE77 ) }

        //{ "lute",  Colour ( 0xffCCCCCC ) },
        //{ "meditation",  Colour ( 0xff62B59D ) },
        //{ "ugen",  Colour ( 0xff1EAE1E ) },
        //{ "arg_listy",  Colour ( 0xff333344 ) },


    };

    CodeEditorComponent::ColourScheme cs;

    for (unsigned int i = 0; i < sizeof(types) / sizeof(types[0]); ++i) { // (NB: numElementsInArray doesn't work here in GCC4.2)
        SkoarLog.w("Colour Scheme", types[i].name, i);
        cs.set(types[i].name, types[i].colour);
    }
    return cs;
}


void SkoarCodeTokeniser::parseSkoarAndPrepareStyles(CodeDocument &source) {

    wstring skoarce(source.getAllContent().toWideCharPointer());

    SkoarLite skoar(skoarce, &SkoarLog);
    auto oldSize = styles.size();
    auto newSize = static_cast<const int>(skoarce.size()) + 1;
    styles.resize(newSize);

    //log.d("syntax_highlight", "skoar.parsed_ok", skoar.parsed_ok, "last_tree", last_tree);
    auto v = &styles;

    auto f = [&v](SkoarNoad* noad) {
        
        if (noad->style != SkoarStyles::EStyle::nostyle) {
            // colour the entire noad...
            auto offs = noad->offs;
            SkoarLog.d("Styling noad", "offs", static_cast<const int>(offs), "size", noad->size, "style", noad->style);
            for (int i = 0; i < noad->size; ++i) {
                const int j = static_cast<const int>(offs) + i;
                v->setUnchecked(j, noad->style);
            }
        }
    };

    if (skoar.parsedOk) {

       // if (lastTree == nullptr)
            skoar.tree->inorder(f);
       /* else {
            int branchNumber = 0;
            for (auto branch : skoar.tree->children) {
            
                if (lastTree->children.size() <= branchNumber) {
                    branch->inorder(f);
                }

                //branch->line_diffs_visit(lastTree->children[branchNumber], f);
                branchNumber++;

            }
        }*/

        //lastTree = skoar.tree;

       //for (auto x : styles)
       //     SkoarLog.e(x);
    }
    else {
        if (newSize > oldSize) {
            for (auto i = oldSize; i < newSize; ++i) {
                styles.setUnchecked(i, SkoarStyles::EStyle::parseFail);
            }
        }
    }
}




