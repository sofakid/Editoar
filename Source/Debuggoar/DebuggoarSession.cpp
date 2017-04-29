#include "DebuggoarSession.h"
#include "DebuggoarDeetsPanel.h"
#include "SkoarProjectionComponent.h"
#include "DebuggoarComponent.h"

// --- DebuggoarSession -----------------------------------------------
DebuggoarSession* session = nullptr;

DebuggoarSession* DebuggoarSession::getInstance () {
    return session;
}

DebuggoarSession::DebuggoarSession (SkoarpionPtr p, String voice, Skoar* skoar) :
    skoarpion (p),
    lock ("DebuggoarSessionLock")
{
    session = this;

    SkoarString v (voice.toWideCharPointer ());
    auto koar = skoar->get_voice (v);

    auto lockRef = &lock;
    auto stateRef = &state;
    auto skoarpionsRef = &skoarpions;


    happening = [=](SkoarEventPtr p) {
        const MessageManagerLock mmLock;
        auto d = DebuggoarDeets::getInstance ();

        d->showKoar (koar);
        d->showEvent (p);
    };

    before_entering_noad_spell = [=](SkoarMinstrelPtr minstrel, SkoarNoadite* noad) {

        if (*stateRef == EState::steppingIn || noad->breakpoint)
        {
            {
                const MessageManagerLock mmLock;
                // select noad in tree
                SkoarProjectionComponent::getInstance ()->selectNoadite (*noad);
                auto d = DebuggoarDeets::getInstance ();
                d->showKoar (koar);
                d->showFairy (minstrel->fairy);
            }

            // highlight text -- do that when selected above.
            lockRef->wait ();
            lockRef->reset ();
        }

        if (*stateRef == EState::stopping)
        {
            throw SkoarNav (SkoarNav::DONE);
        }

#if SKOAR_DEBUG_BUILD
        if (*stateRef == EState::debuggerStepping)
        {
            *stateRef = EState::steppingIn;
            JUCE_BREAK_IN_DEBUGGER;
        }
#endif

    };

    after_entering_noad_spell = [=](SkoarMinstrelPtr p, SkoarNoadite*) {

    };

    before_entering_skoarpuscle_spell = [=](SkoarMinstrelPtr p, SkoarpusclePtr skoarpuscle) {
        // animate fairy doing something
        // or rotate text slightly
    };

    after_entering_skoarpuscle_spell = [=](SkoarMinstrelPtr p, SkoarpusclePtr skoarpuscle) {
        // animate fairy impression
        // fix text
    };

    before_entering_skoarpion_spell = [=](SkoarMinstrelPtr p, SkoarpionPtr skoarpion) {
        {
            const MessageManagerLock mmLock;
            // push old skoarpion 
            //if (current_skoarpion != nullptr) {
            skoarpionsRef->push_back (skoarpion);
            //}

            // select skoarpion tree
            DebuggoarComponent::getDebuggoar ()->selectSkoarpion (skoarpion, v.c_str ());
        }
    };

    after_entering_skoarpion_spell = [=](SkoarMinstrelPtr p, SkoarpionPtr skoarpion) {
        // pop old skoarpion

        if (skoarpionsRef->size () > 1)
        {
            skoarpionsRef->pop_back ();
            auto x = skoarpionsRef->back ();
            if (*stateRef == EState::stopping)
                return;

            const MessageManagerLock mmLock;
            DebuggoarComponent::getDebuggoar ()->selectSkoarpion (x, v.c_str ());
        }

    };

    exiting_spell = [&]() {
        MessageManager::callAsync ([&]() {
            const MessageManagerLock mmLock;
            endSession ();
        });
    };

    MinstrelDebugConfig config (
        before_entering_noad_spell,
        after_entering_noad_spell,
        before_entering_skoarpuscle_spell,
        after_entering_skoarpuscle_spell,
        before_entering_skoarpion_spell,
        after_entering_skoarpion_spell,
        exiting_spell
    );

    m = SkoarMinstrel::NewDebuggingForSkoarpion (L"debuggoar", koar, skoar, skoarpion, happening, config);
    minstrel_thread = new MinstrelThread (m);

}

DebuggoarSession::~DebuggoarSession () {
    die ();
    m = nullptr;
    session = nullptr;
}

DebuggoarSession::MinstrelThread::MinstrelThread (SkoarMinstrelPtr p) :
    Thread (p->name.c_str ()),
    m (p)
{
}

DebuggoarSession::MinstrelThread::~MinstrelThread () {
}


void DebuggoarSession::MinstrelThread::run ()
{
    try
    {
        m->start ();
    }
    catch (SkoarError &)
    {

    }
}

void DebuggoarSession::die () {
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

void DebuggoarSession::start () {
    //state = EState::running;
    state = EState::steppingIn;
    //lock.signal();
    minstrel_thread->startThread ();
}

void DebuggoarSession::stepIn () {
    state = EState::steppingIn;
    lock.signal ();
}

void DebuggoarSession::stepOver () {
    state = EState::steppingOver;
    lock.signal ();
}

void DebuggoarSession::stepOut () {
    state = EState::steppingOut;
    lock.signal ();
}

void DebuggoarSession::continueRunning () {
    state = EState::running;
}

void DebuggoarSession::stop () {
    //state = EState::running;
    state = EState::stopping;
    lock.signal ();
}


void DebuggoarSession::cpp_breakpoint () {
    state = EState::debuggerStepping;
    lock.signal ();
}

void DebuggoarSession::endSession ()
{
    state = EState::stopped;

    auto debuggoar (DebuggoarComponent::getDebuggoar ());
    debuggoar->sessionEnded ();

}

DebuggoarSession::EState DebuggoarSession::getState ()
{
    return state;
}
