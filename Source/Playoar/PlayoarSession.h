#pragma once

#include "../jucer_Headers.h"
#include "skoar.hpp"
#include "minstrel.hpp"

class PlayoarSession
{
    uint64_t t;

public:

    enum class EState
    {
        running,
        stopping,
        stopped
    };

    static PlayoarSession* getInstance ();

    PlayoarSession (String voice, Skoar* skoar);
    ~PlayoarSession ();

    void die ();
    void start ();
    void stop ();
    void endSession ();

    EState getState ();

private:

    class MinstrelThread : public Thread
    {
    public:
        MinstrelThread (SkoarMinstrelPtr);
        ~MinstrelThread () override;
        void run () override;
    private:
        SkoarMinstrelPtr m;
    };

    SpellOfHappening happening;

    volatile EState state;
    WaitableEvent lock;
    SkoarMinstrelPtr m;
    ListOfSkoarpions skoarpions;
    SkoarpionPtr skoarpion;

    ScopedPointer<MinstrelThread> minstrel_thread;
};