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
    auto octaveSkoarpuscle = event->at (L"octave");
    auto noteSkoarpuscle = event->at (L"note");
    auto choardSkoarpuscle = event->at (L"choard");

    int octave (0);
    int note (0);

    if (is_skoarpuscle<SkoarpuscleInt> (octaveSkoarpuscle))
        octave = skoarpuscle_ptr<SkoarpuscleInt> (octaveSkoarpuscle)->val;

    if (is_skoarpuscle<SkoarpuscleInt> (noteSkoarpuscle))
    {
        note = skoarpuscle_ptr<SkoarpuscleInt> (noteSkoarpuscle)->val;
        midiNoteNumbers.clearQuick ();
        midiNoteNumbers.add (12 * octave + note);
    }
    else if (is_skoarpuscle<SkoarpuscleList> (choardSkoarpuscle))
    {
        auto list = skoarpuscle_ptr<SkoarpuscleList> (choardSkoarpuscle)->val;
        midiNoteNumbers.clearQuick ();
        for (auto skoarpuscle : *list)
        {
            if (is_skoarpuscle<SkoarpuscleInt> (skoarpuscle))
            {
                note = skoarpuscle_ptr<SkoarpuscleInt> (skoarpuscle)->val;
                midiNoteNumbers.add (12 * octave + note);
            }
            else if (is_skoarpuscle<SkoarpuscleNoat> (skoarpuscle))
            {
                note = skoarpuscle_ptr<SkoarpuscleNoat> (skoarpuscle)->val;
                midiNoteNumbers.add (12 * octave + note);
            }
        }
    }
}

void Musicker::noteOn ()
{
    auto t = getMidiTime ();
    for (const auto& note : midiNoteNumbers)
    {
        MidiMessage msg (MidiMessage::noteOn (midiChannel, note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
    }
}

void Musicker::noteOff ()
{
    auto t = getMidiTime ();
    for (const auto& note : midiNoteNumbers)
    {
        MidiMessage msg (MidiMessage::noteOff (midiChannel, note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
    }
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
