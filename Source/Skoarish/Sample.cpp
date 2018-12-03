#include "InstrumentManager.h"
#include "Sample.h"

SkoarishSampleInstrument::SkoarishSampleInstrument (File f) :
    SkoarishInstrument(f.getFileNameWithoutExtension ()),
    fileName (f.getFullPathName ()),
    onRenameSpell ([](SkoarishInstrument*) {})
{
}

String SkoarishSampleInstrument::getFileName () {
    return fileName;
}


void SkoarishSampleInstrument::renameFile (File &newFile) {
    auto oldFileName = fileName;
    fileName = newFile.getFullPathName ();
    auto mgr = SkoarishInstrumentManager::getInstance ();
    mgr->updateNewFileName (this, oldFileName);
}

String SkoarishSampleInstrument::renameId (String proposedId) {
    id = makeValidUniqueId (proposedId);

    auto mgr = SkoarishInstrumentManager::getInstance ();
    mgr->updateNewId (this);

    onRenameSpell (this);

    return id;
}

void SkoarishSampleInstrument::setRenameSpell (SpellOfInstruments spell) {
    onRenameSpell = spell;
}

void SkoarishSampleInstrument::unsetRenameSpell () {
    onRenameSpell = [](SkoarishInstrument*) {};
}
