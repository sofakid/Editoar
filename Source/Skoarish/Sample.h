#pragma once
#include "Instrument.h"

class SkoarishSampleInstrument : public SkoarishInstrument
{
public:
    SkoarishSampleInstrument (File);
    String getFileName ();

    String renameId (String);
    void renameFile (File &f);

    void setRenameSpell (SpellOfInstruments);
    void unsetRenameSpell ();

private:
    String id;
    String fileName;

    SpellOfInstruments onRenameSpell;

};