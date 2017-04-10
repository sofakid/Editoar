#include "DebuggoarSession.h"
#include "SkoarpionsComponent.h"

// --- DebuggoarSession -----------------------------------------------
DebuggoarSession* session = nullptr;

DebuggoarSession* DebuggoarSession::getInstance() {
    return session;
}

DebuggoarSession::DebuggoarSession(String voice, Skoar* skoar) :
    lock("DebuggoarSessionLock")
{
    session = this;

    SkoarString v(voice.toWideCharPointer());
    auto koar = skoar->get_voice(v);

    auto lockRef = &lock;
    auto stateRef = &state;
    auto skoarpionsRef = &skoarpions;
    

    happening = [](SkoarEventPtr p) {

    };

    before_entering_noad_spell = [=](SkoarMinstrelPtr minstrel, SkoarNoad* noad) {
        if (*stateRef == EState::steppingIn || noad->breakpoint) {
            {
                const MessageManagerLock mmLock;
                // select noad in tree
                SkoarpionsComponent::getInstance()->selectNoad(noad);
            }

            // highlight text -- do that when selected above.
            lockRef->wait();
            lockRef->reset();
        }
    };

    after_entering_noad_spell = [=](SkoarMinstrelPtr p, SkoarNoad*) {
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
            skoarpionsRef->push_back(skoarpion);
            //}

            // select skoarpion tree
            SkoarpionsComponent::getInstance()->selectSkoarpion(skoarpion, v.c_str());
        }
    };

    after_entering_skoarpion_spell = [=](SkoarMinstrelPtr p, SkoarpionPtr skoarpion) {
        // pop old skoarpion

        if (skoarpionsRef->size() > 1) {
            skoarpionsRef->pop_back();
            auto x = skoarpionsRef->back();
            const MessageManagerLock mmLock;
            SkoarpionsComponent::getInstance()->selectSkoarpion(x, v.c_str());
        }
        
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
    minstrel_thread = new MinstrelThread(m);

}

DebuggoarSession::~DebuggoarSession() {
    m = nullptr;
    session = nullptr;
}

DebuggoarSession::MinstrelThread::MinstrelThread(SkoarMinstrelPtr p) :
    Thread(p->name.c_str()),
    m(p)
{
}

DebuggoarSession::MinstrelThread::~MinstrelThread() {
    stopThread(1000);
}


void DebuggoarSession::MinstrelThread::run()
{
    m->start();
}

void DebuggoarSession::start() {
    //state = EState::running;
    state = EState::steppingIn;
    //lock.signal();
    minstrel_thread->startThread();
}

void DebuggoarSession::stepIn() {
    state = EState::steppingIn;
    lock.signal();
}

void DebuggoarSession::stepOver() {
    state = EState::steppingOver;
    lock.signal();
}

void DebuggoarSession::stepOut() {
    state = EState::steppingOut;
    lock.signal();
}

void DebuggoarSession::continueRunning() {
    state = EState::running;
}