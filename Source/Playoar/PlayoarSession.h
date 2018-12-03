#pragma once

#include "../jucer_Headers.h"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "PlayoarSkoarchestra.h"


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

    PlayoarSession (String voice, Skoar* const skoar);
    ~PlayoarSession ();

    void die ();
    void start ();
    void stop ();
    void endSession ();

    EState getState ();

private:

    SpellOfHappening happening;

    volatile EState state;
    WaitableEvent lock;
    SkoarMinstrelPtr m;
    ListOfSkoarpions skoarpions;
    SkoarpionPtr skoarpion;

    //std::unique_ptr<MinstrelThread> minstrelThread;
    std::unique_ptr<PlayoarSkoarchestra> skoarchestra;
};