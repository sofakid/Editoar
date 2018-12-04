#include "InstrumentManager.h"
#include "MidiInstrument.h"
#include <mutex>

const String idPrefix (TRANS ("midi"));
const int midiPercussionChannel (10);

SkoarishMidiInstrument::SkoarishMidiInstrument (String name, const int program) :
    SkoarishInstrument (idPrefix + name),
    program (program),
    channel (0)
{
}

void SkoarishMidiInstrument::setChannel (int newChannel)
{
    channel = newChannel;
}

void SkoarishMidiInstrument::setChannelAuto ()
{
    channel = SkoarishGeneralMidi::getChannel (this);
}

int SkoarishMidiInstrument::getChannel () const
{
    return channel;
}

SkoarishMidiPercussionInstrument::SkoarishMidiPercussionInstrument (String name, const int note) :
    SkoarishMidiInstrument (name, 1),
    note (note)
{
}

void SkoarishMidiPercussionInstrument::setChannel (int /*newChannel*/)
{
}

void SkoarishMidiPercussionInstrument::setChannelAuto ()
{
}

int SkoarishMidiPercussionInstrument::getChannel () const
{
    return midiPercussionChannel;
}

namespace SkoarishGeneralMidi
{
    void loadInstruments ()
    {
        static int i = 0;
        static SkoarishMidiInstrument normals[] {
            {TRANS ("AcousticGrandPiano"), ++i },
            {TRANS ("BrightAcousticPiano"), ++i },
            {TRANS ("ElectricGrandPiano"), ++i },
            {TRANS ("HonkyTonkPiano"), ++i },
            {TRANS ("ElectricPiano1"), ++i },
            {TRANS ("ElectricPiano2"), ++i },
            {TRANS ("Harpsichord"), ++i },
            {TRANS ("Clavinet"), ++i },

            {TRANS ("Celesta"), ++i },
            {TRANS ("Glockenspiel"), ++i },
            {TRANS ("MusicBox"), ++i },
            {TRANS ("Vibraphone"), ++i },
            {TRANS ("Marimba"), ++i },
            {TRANS ("Xylophone"), ++i },
            {TRANS ("TubularBells"), ++i },
            {TRANS ("Dulcimer"), ++i },

            {TRANS ("DrawbarOrgan"), ++i },
            {TRANS ("PercussiveOrgan"), ++i },
            {TRANS ("RockOrgan"), ++i },
            {TRANS ("ChurchOrgan"), ++i },
            {TRANS ("ReedOrgan"), ++i },
            {TRANS ("Accordion"), ++i },
            {TRANS ("Harmonica"), ++i },
            {TRANS ("TangoAccordion"), ++i },

            {TRANS ("AcousticGuitarNylon"), ++i },
            {TRANS ("AcousticGuitarSteel"), ++i },
            {TRANS ("ElectricGuitarJazz"), ++i },
            {TRANS ("ElectricGuitarClean"), ++i },
            {TRANS ("ElectricGuitarMuted"), ++i },
            {TRANS ("OverdrivenGuitar"), ++i },
            {TRANS ("DistortionGuitar"), ++i },
            {TRANS ("GuitarHarmonics"), ++i },

            {TRANS ("AcousticBass"), ++i },
            {TRANS ("ElectricBassFinger"), ++i },
            {TRANS ("ElectricBassPick"), ++i },
            {TRANS ("FretlessBass"), ++i },
            {TRANS ("SlapBass1"), ++i },
            {TRANS ("SlapBass2"), ++i },
            {TRANS ("SynthBass1"), ++i },
            {TRANS ("SynthBass2"), ++i },

            {TRANS ("Violin"), ++i },
            {TRANS ("Viola"), ++i },
            {TRANS ("Cello"), ++i },
            {TRANS ("Contrabass"), ++i },
            {TRANS ("TremoloStrings"), ++i },
            {TRANS ("PizzicatoStrings"), ++i },
            {TRANS ("OrchestralHarp"), ++i },
            {TRANS ("Timpani"), ++i },

            {TRANS ("StringEnsemble1"), ++i },
            {TRANS ("StringEnsemble2"), ++i },
            {TRANS ("SynthStrings1"), ++i },
            {TRANS ("SynthStrings2"), ++i },
            {TRANS ("ChoirAahs"), ++i },
            {TRANS ("VoiceOohs"), ++i },
            {TRANS ("SynthChoir"), ++i },
            {TRANS ("OrchestralHit"), ++i },

            {TRANS ("Trumpet"), ++i },
            {TRANS ("Trombone"), ++i },
            {TRANS ("Tuba"), ++i },
            {TRANS ("MutedTrumpet"), ++i },
            {TRANS ("FrenchHorn"), ++i },
            {TRANS ("BrassSection"), ++i },
            {TRANS ("SynthBrass1"), ++i },
            {TRANS ("SynthBrass2"), ++i },

            {TRANS ("SopranoSax"), ++i },
            {TRANS ("AltoSax"), ++i },
            {TRANS ("TenorSax"), ++i },
            {TRANS ("BaritoneSax"), ++i },
            {TRANS ("Oboe"), ++i },
            {TRANS ("EnglishHorn"), ++i },
            {TRANS ("Bassoon"), ++i },
            {TRANS ("Clarinet"), ++i },

            {TRANS ("Piccolo"), ++i },
            {TRANS ("Flute"), ++i },
            {TRANS ("Recorder"), ++i },
            {TRANS ("PanFlute"), ++i },
            {TRANS ("BlownFlute"), ++i },
            {TRANS ("Shakuhachi"), ++i },
            {TRANS ("Whistle"), ++i },
            {TRANS ("Ocarina"), ++i },

            {TRANS ("SynthLeadSquare"), ++i },
            {TRANS ("SynthLeadSawtooth"), ++i },
            {TRANS ("SynthLeadCaliope"), ++i },
            {TRANS ("SynthLeadChiff"), ++i },
            {TRANS ("SynthLeadCharang"), ++i },
            {TRANS ("SynthLeadVoice"), ++i },
            {TRANS ("SynthLeadFifths"), ++i },
            {TRANS ("SynthLeadBassLead"), ++i },

            { TRANS ("PadNewAge"), ++i },
            { TRANS ("PadWarm"), ++i },
            { TRANS ("PadPolysynth"), ++i },
            { TRANS ("PadChoir"), ++i },
            { TRANS ("PadBowed"), ++i },
            { TRANS ("PadMetalic"), ++i },
            { TRANS ("PadHalo"), ++i },
            { TRANS ("PadSweep"), ++i },

            { TRANS ("FxRain"), ++i },
            { TRANS ("FxSoundtrack"), ++i },
            { TRANS ("FxCrystal"), ++i },
            { TRANS ("FxAtmosphere"), ++i },
            { TRANS ("FxBrightness"), ++i },
            { TRANS ("FxGoblins"), ++i },
            { TRANS ("FxEchoes"), ++i },
            { TRANS ("FxSciFi"), ++i },

            { TRANS ("Sitar"), ++i },
            { TRANS ("Banjo"), ++i },
            { TRANS ("Shamisen"), ++i },
            { TRANS ("Koto"), ++i },
            { TRANS ("Kalimba"), ++i },
            { TRANS ("Bagpipe"), ++i },
            { TRANS ("Fiddle"), ++i },
            { TRANS ("Shanai"), ++i },

            { TRANS ("TinkleBell"), ++i },
            { TRANS ("Agogo"), ++i },
            { TRANS ("SteelDrums"), ++i },
            { TRANS ("Woodblock"), ++i },
            { TRANS ("TaikoDrum"), ++i },
            { TRANS ("MelodicTom"), ++i },
            { TRANS ("SynthDrum"), ++i },
            { TRANS ("ReverseCymbal"), ++i },

            { TRANS ("GuitarFret"), ++i },
            { TRANS ("Breath"), ++i },
            { TRANS ("Seashore"), ++i },
            { TRANS ("BirdTweet"), ++i },
            { TRANS ("TelephoneRing"), ++i },
            { TRANS ("Helicopter"), ++i },
            { TRANS ("Applause"), ++i },
            { TRANS ("Gunshot"), ++i },

        };

        static int j = 34;
        static SkoarishMidiPercussionInstrument percussions[] {
            {TRANS ("BassDrum2"), ++j },
            {TRANS ("BassDrum1"), ++j },
            {TRANS ("RimShot"), ++j },
            {TRANS ("SnareDrum1"), ++j },
            {TRANS ("HandClap"), ++j },

            {TRANS ("SnareDrum2"), ++j },
            {TRANS ("LowTom2"), ++j },
            {TRANS ("ClosedHiHat"), ++j },
            {TRANS ("LowTom1"), ++j },
            {TRANS ("PedalHiHat"), ++j },
            {TRANS ("MidTom2"), ++j },
            {TRANS ("OpenHiHat"), ++j },
            {TRANS ("MidTom1"), ++j },
            {TRANS ("HighTom2"), ++j },
            {TRANS ("CrashCymbal1"), ++j },

            {TRANS ("HighTom1"), ++j },
            {TRANS ("RideCymbal1"), ++j },
            {TRANS ("ChineseCymbal"), ++j },
            {TRANS ("RideBell"), ++j },
            {TRANS ("Tambourine"), ++j },
            {TRANS ("SplashCymbal"), ++j },
            {TRANS ("Cowbell"), ++j },
            {TRANS ("CrashCymbal2"), ++j },
            {TRANS ("VibraSlap"), ++j },
            {TRANS ("RideCymbal2"), ++j },

            {TRANS ("HighBongo"), ++j },
            {TRANS ("LowBongo"), ++j },
            {TRANS ("MuteHighConga"), ++j },
            {TRANS ("OpenHighConga"), ++j },
            {TRANS ("LowConga"), ++j },
            {TRANS ("HighTimbale"), ++j },
            {TRANS ("LowTimbale"), ++j },
            {TRANS ("HighAgogo"), ++j },
            {TRANS ("LowAgogo"), ++j },
            {TRANS ("Cabasa"), ++j },

            {TRANS ("Maracas"), ++j },
            {TRANS ("ShortWhistle"), ++j },
            {TRANS ("LongWhistle"), ++j },
            {TRANS ("ShortGuiro"), ++j },
            {TRANS ("LongGuiro"), ++j },
            {TRANS ("Claves"), ++j },
            {TRANS ("HigHWoodBlock"), ++j },
            {TRANS ("LowWoodBlock"), ++j },
            {TRANS ("MuteCuica"), ++j },
            {TRANS ("OpenCuica"), ++j },

            {TRANS ("MuteTriangle"), ++j },
            {TRANS ("OpenTriangle"), ++j }

        };

    }

    // todo, this is dirrrrty.

    const int minChannel = 1;
    const int maxChannel = 16;
    const int maxChannels = 15;

    std::mutex channelsMutex;
    std::map<const SkoarishMidiInstrument*, int> channelCounter;
    const SkoarishMidiInstrument* allocatedChannels[maxChannels];

    int usedChannels () {
        int n = 0;
        for (auto& kv : channelCounter)
            if (kv.second > 0)
                ++n;
        return n;
    }

    int findChannel (const SkoarishMidiInstrument* const instrument) {
        int i = 1;
        for (auto& p : allocatedChannels)
        {
            if (p == instrument)
                return i;

            if (++i == midiPercussionChannel)
                ++i;
        }

        return i;
    }

    int findFreeIndex () {
        for (int i = 0; i < maxChannels; ++i)
            if (allocatedChannels[i] == nullptr)
                return i;

        return -1;
    }

    int getChannel (const SkoarishMidiInstrument* const instrument)
    {
        static bool initialized (false);
        const std::lock_guard<std::mutex> lock (channelsMutex);
        
        if (!initialized)
        {
            for (int i = 0; i < maxChannels; ++i)
                allocatedChannels[i] = nullptr;
            initialized = true;
        }

        int used (usedChannels ());
        if (used > maxChannels)
        {
            jassertfalse;
            return 0;
        }

        auto entry (channelCounter[instrument]);
        if (entry == 0)
        {
            ++used;
            if (used > maxChannels)
            {
                jassertfalse;
                return 0;
            }
            const int i = findFreeIndex ();
            if (i == -1)
                return 0;

            allocatedChannels[i] = instrument;
        }

        channelCounter[instrument] += 1;

        return findChannel(instrument);
    }

    void releaseChannel (const SkoarishMidiInstrument* const instrument)
    {
        if (instrument == nullptr)
            return;

        const std::lock_guard<std::mutex> lock (channelsMutex);

        const auto entry (channelCounter[instrument]);
        if (entry > 0)
        {
            channelCounter[instrument] -= 1;
        }

        if (entry == 1)
        {
            for (int i = 0; i < maxChannels; ++i)
                if (allocatedChannels[i] == instrument)
                {
                    allocatedChannels[i] = nullptr;
                    break;
                }
        }
    }

}

