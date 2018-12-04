#include "InstrumentManager.h"
#include "Instrument.h"
#include "MidiInstrument.h"
#include "Sample.h"

SkoarishInstrumentManager* SkoarishInstrumentManager::getInstance () {
    static bool initialized = false;
    static SkoarishInstrumentManager* instance (nullptr);

    if (initialized == false)
    {
        instance = new SkoarishInstrumentManager ();
        initialized = true;
        SkoarishGeneralMidi::loadInstruments ();
    }
    return instance;
}

SkoarishInstrumentManager::SkoarishInstrumentManager () {

}

SkoarishInstrumentManager::~SkoarishInstrumentManager () {

}


void SkoarishInstrumentManager::addInstrument (SkoarishInstrument *instr) {
    std::lock_guard<std::mutex> lock (mapsMutex);

    id_to_instrument_map[instr->getId ()] = instr;
    SkoarishSampleInstrument* p = dynamic_cast<SkoarishSampleInstrument*> (instr);
    if (p != nullptr)
        file_to_id_map[p->getFileName ()] = p->getId ();
}

SkoarishInstrument* SkoarishInstrumentManager::getInstrument (String &id) {
    std::lock_guard<std::mutex> lock (mapsMutex);
    
    auto x = id_to_instrument_map[id];
    return x;
}

SkoarishSampleInstrument* SkoarishInstrumentManager::getOrCreateInstrumentByFile (File &file) {
    {
        std::lock_guard<std::mutex> lock (mapsMutex);

        auto id = file_to_id_map[file.getFullPathName ()];
        if (id != String (L""))
            return static_cast<SkoarishSampleInstrument*> (id_to_instrument_map[id]);
    }
    return new SkoarishSampleInstrument (file);
    
}

// --- renaming -----------------------------------------------------------

void SkoarishInstrumentManager::updateNewId (SkoarishSampleInstrument* instr) {
    std::lock_guard<std::mutex> lock (mapsMutex);

    auto fileName = instr->getFileName ();
    auto oldId = file_to_id_map[fileName];
    auto newId = instr->getId ();

    file_to_id_map[fileName] = newId;
    id_to_instrument_map[oldId] = nullptr;
    id_to_instrument_map[newId] = instr;
}

void SkoarishInstrumentManager::updateNewFileName (SkoarishSampleInstrument* instr, String oldFileName) {
    std::lock_guard<std::mutex> lock (mapsMutex);

    auto fileName = instr->getFileName ();

    file_to_id_map[oldFileName] = String (L"");
    file_to_id_map[fileName] = instr->getId ();
}


// --- removing -----------------------------------------------------------
void SkoarishInstrumentManager::removeByFileName (String fileName) {
    std::lock_guard<std::mutex> lock (mapsMutex);

    auto id = file_to_id_map[fileName];

    file_to_id_map[fileName] = String (L"");
    id_to_instrument_map[id] = nullptr;
}

void SkoarishInstrumentManager::removeById (String id) {
    std::lock_guard<std::mutex> lock (mapsMutex);

    auto instr = id_to_instrument_map[id];

    if (instr != nullptr)
    {
        id_to_instrument_map[id] = nullptr;
        SkoarishSampleInstrument* p = dynamic_cast<SkoarishSampleInstrument*> (instr);
        if (p != nullptr)
            file_to_id_map[p->getFileName ()] = String (L"");
    }
}