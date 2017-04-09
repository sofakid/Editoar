#include "DebuggoarSession.h"
#include "SkoarpionsComponent.h"

// --- DebuggoarSession -----------------------------------------------

DebuggoarSession::DebuggoarSession(String voice, Skoar* skoar)
{
    SkoarString v(voice.toWideCharPointer());
    auto koar = skoar->get_voice(v);

    SpellOfHappening happening = [](SkoarEventPtr p) {

    };
    
    SpellOfDebuggingNoads before_entering_noad_spell = [=](SkoarMinstrelPtr, SkoarNoad* noad) {
        // select noad in tree
        SkoarpionsComponent::getInstance()->selectNoad(noad);

        // highlight text -- do that when selected above.
    };

    SpellOfDebuggingNoads after_entering_noad_spell = [=](SkoarMinstrelPtr p, SkoarNoad*) {
    };

    SpellOfDebuggingSkoarpuscles before_entering_skoarpuscle_spell = [=](SkoarMinstrelPtr p, SkoarpusclePtr skoarpuscle) {
        // animate fairy doing something
        // or rotate text slightly
    };

    SpellOfDebuggingSkoarpuscles after_entering_skoarpuscle_spell = [=](SkoarMinstrelPtr p, SkoarpusclePtr skoarpuscle) {
        // animate fairy impression
        // fix text
    };

    SpellOfDebuggingSkoarpions before_entering_skoarpion_spell = [=](SkoarMinstrelPtr p, SkoarpionPtr skoarpion) {
        // push old skoarpion 
        // select skoarpion tree

    };

    SpellOfDebuggingSkoarpions after_entering_skoarpion_spell = [=](SkoarMinstrelPtr p, SkoarpionPtr skoarpion) {
        // pop old skoarpion
        // select popped skoarpion tree
    };

    MinstrelDebugConfig config(
        before_entering_noad_spell,
        after_entering_noad_spell,
        before_entering_skoarpuscle_spell,
        after_entering_skoarpuscle_spell,
        before_entering_skoarpion_spell,
        after_entering_skoarpion_spell
    );

    m = SkoarMinstrel::NewDebugging(L"debuggoar", koar, skoar, happening, config);
}

DebuggoarSession::~DebuggoarSession() {
    m = nullptr;
}