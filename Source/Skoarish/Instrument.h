#pragma once

#include "../jucer_Headers.h"

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

private:
    String id;
    String fileName;

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
