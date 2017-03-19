#include "Instrument.h"
#include <regex>

SkoarishInstrument::SkoarishInstrument(File f) :
    fileName(f.getFullPathName())
{
    auto mgr = SkoarishInstrumentManager::getInstance();
    id = makeValidUniqueId(f.getFileNameWithoutExtension());
    mgr->addInstrument(this);
    onRenameSpell = [](SkoarishInstrument*) {};
}

SkoarishInstrument::~SkoarishInstrument() {
    auto mgr = SkoarishInstrumentManager::getInstance();
    mgr->removeById(id);
}

String SkoarishInstrument::getId() {
    return id;
}

String SkoarishInstrument::getFileName() {
    return fileName;
}

String SkoarishInstrument::makeValidUniqueId(String dirty) {
    auto s = makeValidId(dirty);

    int i = 0;
    auto mgr = SkoarishInstrumentManager::getInstance();

    SkoarishInstrument* x = mgr->getInstrument(s);
    String attempt = s;
    while (x != nullptr) {
        attempt = s + L"_" + String(i++);
        x = mgr->getInstrument(attempt);
    }
    
    return attempt;
}

String SkoarishInstrument::makeValidId(String dirty) {
    dirty = dirty.trim().trimCharactersAtStart(String(L"@"));

    std::wstring s(dirty.toWideCharPointer());
    std::wregex e(L"([^a-zA-Z0-9_]+)");

    std::wstring clean = L"@" + std::regex_replace(s, e, L"_");

    return String(clean.c_str());
}

String SkoarishInstrument::renameId(String proposedId) {
    id = makeValidUniqueId(proposedId);
    
    auto mgr = SkoarishInstrumentManager::getInstance();
    mgr->updateNewId(this);

    onRenameSpell(this);

    return id;
}

void SkoarishInstrument::renameFile(File &newFile) {
    auto oldFileName = fileName;
    fileName = newFile.getFullPathName();
    auto mgr = SkoarishInstrumentManager::getInstance();
    mgr->updateNewFileName(this, oldFileName);
}

void SkoarishInstrument::setRenameSpell(SpellOfInstruments spell) {
    onRenameSpell = spell;
}

void SkoarishInstrument::unsetRenameSpell() {
    onRenameSpell = [](SkoarishInstrument*) {};
}

// --- manager ----------------------------------------------------------

SkoarishInstrumentManager* SkoarishInstrumentManager::getInstance() {
    static bool initialized = false;
    static SkoarishInstrumentManager* instance;

    if (initialized == false) {
        instance = new SkoarishInstrumentManager();
        initialized = true;
    }
    return instance;
}

SkoarishInstrumentManager::SkoarishInstrumentManager() {

}

SkoarishInstrumentManager::~SkoarishInstrumentManager() {

}


void SkoarishInstrumentManager::addInstrument(SkoarishInstrument *instr) {
    id_to_instrument_map[instr->getId()] = instr;
    file_to_id_map[instr->getFileName()] = instr->getId();
}

SkoarishInstrument* SkoarishInstrumentManager::getInstrument(String &id) {
    auto x = id_to_instrument_map[id];

    return x;
}

SkoarishInstrument* SkoarishInstrumentManager::getOrCreateInstrumentByFile(File &file) {
    auto id = file_to_id_map[file.getFullPathName()];
    if (id == String(L"")) {
        return new SkoarishInstrument(file);
    }
    return id_to_instrument_map[id];
}

// --- renaming -----------------------------------------------------------

void SkoarishInstrumentManager::updateNewId(SkoarishInstrument* instr) {
    auto fileName = instr->getFileName();
    auto oldId = file_to_id_map[fileName];
    auto newId = instr->getId();

    file_to_id_map[fileName] = newId;
    id_to_instrument_map[oldId] = nullptr;
    id_to_instrument_map[newId] = instr;
}

void SkoarishInstrumentManager::updateNewFileName(SkoarishInstrument* instr, String oldFileName) {
    auto fileName = instr->getFileName();

    file_to_id_map[oldFileName] = String(L"");
    file_to_id_map[fileName] = instr->getId();
}


// --- removing -----------------------------------------------------------
void SkoarishInstrumentManager::removeByFileName(String fileName) {
    auto id = file_to_id_map[fileName];

    file_to_id_map[fileName] = String(L"");
    id_to_instrument_map[id] = nullptr;
}

void SkoarishInstrumentManager::removeById(String id) {
    auto instr = id_to_instrument_map[id];

    if (instr != nullptr) {
        file_to_id_map[instr->getFileName()] = String(L"");
        id_to_instrument_map[id] = nullptr;
    }
}