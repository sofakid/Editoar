#pragma once
#include "../jucer_Headers.h"
#include "skoar.hpp"
#include "minstrel.hpp"

class DebuggoarSession {
public:

    enum class EState {
        running,
        steppingIn,
        steppingOver,
        steppingOut
    };

    static DebuggoarSession* getInstance();

    DebuggoarSession(String voice, Skoar* skoar);
    ~DebuggoarSession();

    void start();

    void stepIn();
    void stepOut();
    void stepOver();

    void continueRunning();

private:    
    
    class MinstrelThread : public Thread {
    public:
        MinstrelThread(SkoarMinstrelPtr);
        ~MinstrelThread() override;
        void run() override;
    private:
        SkoarMinstrelPtr m;
    };

    SpellOfHappening happening;
    SpellOfDebuggingNoads before_entering_noad_spell;
    SpellOfDebuggingNoads after_entering_noad_spell;
    SpellOfDebuggingSkoarpuscles before_entering_skoarpuscle_spell;
    SpellOfDebuggingSkoarpuscles after_entering_skoarpuscle_spell;
    SpellOfDebuggingSkoarpions before_entering_skoarpion_spell;
    SpellOfDebuggingSkoarpions after_entering_skoarpion_spell;

    EState state;
    WaitableEvent lock;
    SkoarMinstrelPtr m;
    ListOfSkoarpions skoarpions;

    ScopedPointer<MinstrelThread> minstrel_thread;
};