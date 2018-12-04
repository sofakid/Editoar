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
    auto instrumentSkoarpuscle = event->at (L"instrument");
    String x (skoarpuscle_val<SkoarpuscleSymbol> (instrumentSkoarpuscle, defaultInstrumentId).c_str ());
    String instId (L"@");
    instId << x;

    if (instrument == nullptr || instId != instrumentId)
    {
        auto oldInstrument = instrument;

        instrumentId = instId;
        auto p = SkoarishInstrumentManager::getInstance ()->getInstrument (instrumentId);
        instrument = dynamic_cast<SkoarishMidiInstrument*>(p);

        if (instrument != nullptr)
        {
            isPercussion = (dynamic_cast<SkoarishMidiPercussionInstrument*> (instrument) != nullptr);

            if (!isPercussion)
            {
                SkoarishGeneralMidi::releaseChannel (oldInstrument);
                instrument->setChannelAuto ();
            }
            MidiMessage msg (MidiMessage::programChange (instrument->getChannel (), instrument->program));
            msg.setTimeStamp (getMidiTime ());
            midiOutDevice->sendMessageNow (msg);
        }
    }

    auto octaveSkoarpuscle = event->at (L"octave");
    auto noteSkoarpuscle = event->at (L"note");
    auto choardSkoarpuscle = event->at (L"choard");

    const int defaultOctave (5);
    int octave = skoarpuscle_val<SkoarpuscleInt> (octaveSkoarpuscle, defaultOctave);

    if (is_skoarpuscle<SkoarpuscleInt> (noteSkoarpuscle))
    {
        int note = skoarpuscle_ptr<SkoarpuscleInt> (noteSkoarpuscle)->val;
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
                int note = skoarpuscle_ptr<SkoarpuscleInt> (skoarpuscle)->val;
                midiNoteNumbers.add (12 * octave + note);
            }
            else if (is_skoarpuscle<SkoarpuscleNoat> (skoarpuscle))
            {
                int note = skoarpuscle_ptr<SkoarpuscleNoat> (skoarpuscle)->val;
                midiNoteNumbers.add (12 * octave + note);
            }
        }
    }
}

void Musicker::noteOn ()
{
    if (instrument == nullptr)
        return;

    auto t = getMidiTime ();
    if (isPercussion)
    {
        auto perc = dynamic_cast<SkoarishMidiPercussionInstrument*> (instrument);
        MidiMessage msg (MidiMessage::noteOn (instrument->getChannel (), perc->note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
        return;
    }

    for (const auto& note : midiNoteNumbers)
    {
        MidiMessage msg (MidiMessage::noteOn (instrument->getChannel (), note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
    }
}

void Musicker::noteOff ()
{
    if (instrument == nullptr)
        return;

    auto t = getMidiTime ();
    if (isPercussion)
    {
        auto perc = dynamic_cast<SkoarishMidiPercussionInstrument*> (instrument);
        MidiMessage msg (MidiMessage::noteOff (instrument->getChannel (), perc->note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
        return;
    }

    for (const auto& note : midiNoteNumbers)
    {
        MidiMessage msg (MidiMessage::noteOff (instrument->getChannel (), note, velocity));
        msg.setTimeStamp (t);
        midiOutDevice->sendMessageNow (msg);
    }
}

void Musicker::startMidi ()
{
    midiOutDevice.reset (MidiOutput::openDevice (midiDeviceIndex));
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

SkoarFloat Musicker::getTime ()
{
    return static_cast<SkoarFloat> (Time::getMillisecondCounterHiRes ());
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
