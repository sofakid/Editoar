#pragma once
#include "Instrument.h"

class SkoarishMidiInstrument : public SkoarishInstrument
{
public:
    SkoarishMidiInstrument (String name, const int program);
    
    virtual void setChannel (int newChannel);
    virtual void setChannelAuto ();
    virtual int getChannel () const;

    const int program;
private:
    int channel;

};

class SkoarishMidiPercussionInstrument : public SkoarishMidiInstrument
{
public:
    SkoarishMidiPercussionInstrument (String name, const int note);

    void setChannel (int newChannel) override;
    void setChannelAuto () override;
    int getChannel () const override;
    const int note;
};

namespace SkoarishGeneralMidi
{
    void loadInstruments ();
    
    int getChannel (const SkoarishMidiInstrument* const);
    void releaseChannel (const SkoarishMidiInstrument* const);
}