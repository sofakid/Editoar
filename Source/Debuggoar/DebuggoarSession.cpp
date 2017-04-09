#include "DebuggoarSession.h"

// --- DebuggoarSession -----------------------------------------------

DebuggoarSession::DebuggoarSession(String voice, Skoar* skoar)
{
    SkoarString v(voice.toWideCharPointer());
    auto koar = skoar->get_voice(v);

    SpellOfHappening happening = [](SkoarEventPtr p) {

    };
    
    SpellOfMinstrels before_entering_noad_spell = [&](SkoarMinstrelPtr p) {

    };

    SpellOfMinstrels after_entering_noad_spell = [&](SkoarMinstrelPtr p) {

    };

    SpellOfMinstrels before_entering_skoarpuscle_spell = [&](SkoarMinstrelPtr p) {

    };

    SpellOfMinstrels after_entering_skoarpuscle_spell = [&](SkoarMinstrelPtr p) {

    };

    SpellOfMinstrels before_entering_skoarpion_spell = [&](SkoarMinstrelPtr p) {

    };

    SpellOfMinstrels after_entering_skoarpion_spell = [&](SkoarMinstrelPtr p) {

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