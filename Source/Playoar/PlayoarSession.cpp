#include "PlayoarSession.h"
#include "../Logging/SkoarLogger.hpp"


// --- PlayoarSession -----------------------------------------------
PlayoarSession* session = nullptr;

PlayoarSession* PlayoarSession::getInstance () {
    return session;
}

PlayoarSession::PlayoarSession (String voice, Skoar* const skoar)
{
    session = this;
    t = 0;

    happening = [&, this](SkoarEventPtr p) {

        //const MessageManagerLock mmLock;
        //SkoarLog.i (L"IT'S HAPPENNING!!! t=", t);
        //for (auto& x : p->table)
        //{
        //    auto& key = x.first;
        //    auto val = x.second != nullptr ? x.second : make_skoarpuscle (nullptr);
        //    SkoarLog.i (L"    ", key, L": ", val->valAsString());
        //}
        //auto& state (*stateRef);
    };

    //SkoarString v (voice.toWideCharPointer ());
    //auto koar = skoar->get_voice (v);
    //m = SkoarMinstrel::New (L"playoar", koar, skoar, happening);
    //m->musicker.reset (new Musicker ());
    //minstrelThread.reset(new MinstrelThread (m));
    skoarchestra.reset (new PlayoarSkoarchestra (skoar, happening));
}

PlayoarSession::~PlayoarSession () {
    m = nullptr;
    session = nullptr;
    die ();
}

void PlayoarSession::die () {
    if (skoarchestra == nullptr)
        return;

    skoarchestra->stopThreads ();

    skoarchestra = nullptr;
}

void PlayoarSession::start () {
    state = EState::running;
    //lock.signal();
    skoarchestra->startThreads ();
}

void PlayoarSession::stop () {
    //state = EState::running;
    state = EState::stopping;
    lock.signal ();
}

void PlayoarSession::endSession ()
{
    state = EState::stopped;

    //auto debuggoar (DebuggoarComponent::getDebuggoar ());
    //debuggoar->sessionEnded ();

}

PlayoarSession::EState PlayoarSession::getState ()
{
    return state;
}
