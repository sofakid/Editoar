#pragma once
#include "../jucer_Headers.h"
#include <mutex>

class SkoarishInstrument;
class SkoarishSampleInstrument;
class SkoarishMidiInstrument;

class SkoarishInstrumentManager
{
public:
    static SkoarishInstrumentManager* getInstance ();

    SkoarishInstrumentManager ();
    ~SkoarishInstrumentManager ();

    void addInstrument (SkoarishInstrument*);

    SkoarishInstrument* getInstrument (String &);
    SkoarishSampleInstrument* getOrCreateInstrumentByFile (File &file);

    void updateNewId (SkoarishSampleInstrument* instr);
    void updateNewFileName (SkoarishSampleInstrument* instr, String oldFileName);

    void removeByFileName (String fileName);
    void removeById (String id);

private:
    std::mutex mapsMutex;
    std::map<String, SkoarishInstrument*> id_to_instrument_map;
    std::map<String, String> file_to_id_map;
};