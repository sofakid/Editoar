#pragma once
#include "../jucer_Headers.h"
#include "minstrel.hpp"
#include <vector>

class MinstrelThread : public Thread
{
public:
    MinstrelThread (SkoarMinstrelPtr);
    ~MinstrelThread () override;
    void run () override;
private:
    SkoarMinstrelPtr m;
};

class Musicker : public ISkoarMinstrelMusicker
{
    std::unique_ptr<MidiOutput> midiOutDevice;
    int midiDeviceIndex = 0;
    int midiChannel = 1;
    int midiProgramNumber = 1;
    int midiNoteNumber = 40;
    float velocity = 0.7f;

    Array<int> midiNoteNumbers;

    MinstrelThread* const thread;

public:
    Musicker (MinstrelThread* const);

    void config (SkoarEventPtr event) override;
    void noteOn () override;
    void noteOff () override;

    void startMidi ();
    void stopMidi ();

    double getMidiTime ();

    void sleep (int ms) override;
    SkoarFloat getTime () override;
};


class PlayoarSkoarchestra : public Skoarchestra
{
    OwnedArray<MinstrelThread> threads;

public:
    PlayoarSkoarchestra (Skoar* const, const SpellOfHappening&);

    void startThreads ();
    void stopThreads ();
};