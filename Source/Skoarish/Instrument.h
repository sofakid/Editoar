#pragma once

#include "../jucer_Headers.h"
#include <functional>

class SkoarishInstrument;
typedef std::function<void(SkoarishInstrument*)> SpellOfInstruments;

class SkoarishInstrument
{
public:
    SkoarishInstrument(File);
    ~SkoarishInstrument();
    String getId();
    String getFileName();
    static String makeValidId(String);
    static String makeValidUniqueId(String dirty);

    String renameId(String);
    void renameFile(File &f);

    void setRenameSpell(SpellOfInstruments);
    void unsetRenameSpell();
    
private:
    String id;
    String fileName;

    SpellOfInstruments onRenameSpell;

};

class SkoarishInstrumentManager
{
public:
    static SkoarishInstrumentManager* getInstance();
    
    SkoarishInstrumentManager();
    ~SkoarishInstrumentManager();

    void addInstrument(SkoarishInstrument*);

    SkoarishInstrument* getInstrument(String &);
    SkoarishInstrument* getOrCreateInstrumentByFile(File &file);

    void updateNewId(SkoarishInstrument* instr);
    void updateNewFileName(SkoarishInstrument* instr, String oldFileName);

    void removeByFileName(String fileName);
    void removeById(String id);

private:
    std::map<String, SkoarishInstrument*> id_to_instrument_map;
    std::map<String, String> file_to_id_map;

};
