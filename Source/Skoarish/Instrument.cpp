#include "Instrument.h"
#include "InstrumentManager.h"
#include <regex>


SkoarishInstrument::SkoarishInstrument (String id) :
    id (makeValidUniqueId (id))
{
    auto mgr = SkoarishInstrumentManager::getInstance ();
    mgr->addInstrument (this);
}

SkoarishInstrument::~SkoarishInstrument() {
    auto mgr = SkoarishInstrumentManager::getInstance();
    mgr->removeById(id);
}

String SkoarishInstrument::getId() {
    return id;
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
