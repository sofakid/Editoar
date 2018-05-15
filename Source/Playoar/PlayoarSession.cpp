#include "PlayoarSession.h"
#include "../Logging/SkoarLogger.hpp"


// --- PlayoarSession -----------------------------------------------
PlayoarSession* session = nullptr;

PlayoarSession* PlayoarSession::getInstance () {
    return session;
}

PlayoarSession::PlayoarSession (String voice, Skoar* skoar)
{
    session = this;
    t = 0;

    happening = [&, this](SkoarEventPtr p) {
        const MessageManagerLock mmLock;

        auto bps = skoarpuscle_ptr<SkoarpuscleFloat> (p->at (L"bps"))->val;
        auto dur = skoarpuscle_ptr<SkoarpuscleFloat> (p->at (L"dur"))->val;

        uint64_t durMs = static_cast<uint64_t>((1000.0 / bps) * dur);

        uint64_t start = t;
        t += durMs;
        uint64_t end = t;

        SkoarLog.i (L"IT'S HAPPENNING!!! t=", t);
        for (auto& x : p->table)
        {
            auto& key = x.first;
            auto val = x.second != nullptr ? x.second : make_skoarpuscle (nullptr);
            SkoarLog.i (L"    ", key, L": ", val->valAsString());
        }
        //auto& state (*stateRef);
    };

    SkoarString v (voice.toWideCharPointer ());
    auto koar = skoar->get_voice (v);
    m = SkoarMinstrel::New (L"playoar", koar, skoar, happening);
    minstrel_thread = new MinstrelThread (m);
}

PlayoarSession::~PlayoarSession () {
    m = nullptr;
    session = nullptr;
}

PlayoarSession::MinstrelThread::MinstrelThread (SkoarMinstrelPtr p) :
    Thread (p->name.c_str ()),
    m (p)
{
}

PlayoarSession::MinstrelThread::~MinstrelThread () {
}


void PlayoarSession::MinstrelThread::run ()
{
    try
    {
        m->start ();
    }
    catch (SkoarError &)
    {

    }
}

void PlayoarSession::die () {
    if (minstrel_thread == nullptr)
        return;

    bool died (minstrel_thread->waitForThreadToExit (10));

    if (!died)
    {
        stop ();
        died = minstrel_thread->waitForThreadToExit (3000);
    }

    if (!died)
    {
        minstrel_thread->stopThread (500);
    }

    minstrel_thread = nullptr;
}

void PlayoarSession::start () {
    state = EState::running;
    //lock.signal();
    minstrel_thread->startThread ();
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
