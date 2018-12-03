#include "PlayoarSkoarchestra.h"

MinstrelThread::MinstrelThread (SkoarMinstrelPtr p) :
    Thread (p->name.c_str ()),
    m (p)
{
}

MinstrelThread::~MinstrelThread ()
{
}


void MinstrelThread::run ()
{
    try
    {
        m->start ();
    }
    catch (SkoarError &)
    {

    }
}


Musicker::Musicker (MinstrelThread* const thread) :
    thread (thread)
{
    startMidi ();
}

void Musicker::config (SkoarEventPtr event)
{
    auto noteSkoarpuscle = event->at (L"note");
    auto octaveSkoarpuscle = event->at (L"octave");

    int note (0);
    int octave (0);

    if (is_skoarpuscle<SkoarpuscleInt> (noteSkoarpuscle))
        note = skoarpuscle_ptr<SkoarpuscleInt> (noteSkoarpuscle)->val;

    if (is_skoarpuscle<SkoarpuscleInt> (octaveSkoarpuscle))
        octave = skoarpuscle_ptr<SkoarpuscleInt> (octaveSkoarpuscle)->val;

    midiNoteNumber = 12 * octave + note;
}

void Musicker::noteOn ()
{
    MidiMessage msg (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
    msg.setTimeStamp (getMidiTime ());
    midiOutDevice->sendMessageNow (msg);
}

void Musicker::noteOff ()
{
    MidiMessage msg (MidiMessage::noteOff (midiChannel, midiNoteNumber, velocity));
    msg.setTimeStamp (getMidiTime ());
    midiOutDevice->sendMessageNow (msg);
}

void Musicker::startMidi ()
{
    midiOutDevice.reset (MidiOutput::openDevice (midiDeviceIndex));
    MidiMessage msg (MidiMessage::programChange (1, 1));
    msg.setTimeStamp (getMidiTime ());
    midiOutDevice->sendMessageNow (msg);
}

void Musicker::stopMidi ()
{
    midiOutDevice.reset ();
}

double Musicker::getMidiTime ()
{
    return Time::getMillisecondCounterHiRes () * 0.001;
}

void Musicker::sleep (int ms)
{
    thread->sleep (ms);
}

PlayoarSkoarchestra::PlayoarSkoarchestra (Skoar* const skoar, const SpellOfHappening& happeningSpell) :
    Skoarchestra(skoar, happeningSpell)
{
    for (auto& minstrel: minstrels)
    {
        auto thread = new MinstrelThread (minstrel);
        minstrel->musicker.reset (new Musicker (thread));
        threads.add (thread);
    }
}

void PlayoarSkoarchestra::startThreads ()
{
    for (auto t : threads)
        t->startThread (Thread::realtimeAudioPriority);
}

void PlayoarSkoarchestra::stopThreads ()
{
    for (auto t : threads)
    {
        // todo send something to stop them
        bool died (t->waitForThreadToExit (10));

        if (!died)
        {
            died = t->waitForThreadToExit (3000);
        }

        if (!died)
        {
            t->stopThread (500);
        }
    }
}
