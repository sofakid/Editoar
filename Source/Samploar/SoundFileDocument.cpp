#include "SoundFileDocument.h"
#include "SamploarComponent.h"
#include "../Skoarish/InstrumentManager.h"


SoundFileDocument::SoundFileDocument(Project* p, const File& f)
    : project(p), file(f)
{
    reloadFromFile();

    // todo: save name in project

    auto mgr = SkoarishInstrumentManager::getInstance();

    instrument = mgr->getOrCreateInstrumentByFile(file);
}

//==============================================================================
bool SoundFileDocument::Type::canOpenFile(const File& file)
{
    if (file.hasFileExtension("wav;WAV"))
        return true;

    return false;
}

OpenDocumentManager::Document* SoundFileDocument::Type::openFile(Project* p, const File& file)
{ 
    return new SoundFileDocument(p, file); 
}

//=== overrides ===========================================================================
bool SoundFileDocument::loadedOk() const 
{ 
    return true; 
}

bool SoundFileDocument::isForFile(const File& f) const
{ 
    return file == f; 
}

bool SoundFileDocument::isForNode(const ValueTree&) const
{ 
    return false; 
}

bool SoundFileDocument::SoundFileDocument::refersToProject(Project& p) const
{ 
    return project == &p;
}

Project* SoundFileDocument::getProject() const
{ 
    return project; 
}

bool SoundFileDocument::SoundFileDocument::needsSaving() const
{ 
    return false; 
}

bool SoundFileDocument::save()
{ 
    return true; 
}

bool SoundFileDocument::saveAs()
{ 
    return false; 
}

bool SoundFileDocument::hasFileBeenModifiedExternally()
{ 
    return fileModificationTime != file.getLastModificationTime(); 
}

void SoundFileDocument::reloadFromFile()
{ 
    fileModificationTime = file.getLastModificationTime(); 
}

String SoundFileDocument::getName() const
{ 
    return getFile().getFileName(); 
}

File SoundFileDocument::getFile() const
{
    return file; 
}

Component* SoundFileDocument::createEditor()
{ 
    return new SamploarComponent(this); 
}

Component* SoundFileDocument::createViewer() {
    return createEditor(); 
}

void SoundFileDocument::fileHasBeenRenamed(const File& newFile)
{
    file = newFile; 
}

String SoundFileDocument::getState() const
{ 
    return String(); 
}

void SoundFileDocument::restoreState(const String&)
{
}

String SoundFileDocument::getType() const
{
    if (file.getFileExtension().isNotEmpty())
        return file.getFileExtension() + " file";

    jassertfalse;
    return "Unknown";
}


//=== customs ===========================================================================

SkoarishSampleInstrument* SoundFileDocument::getInstrument() {
    return instrument;
}

String SoundFileDocument::renameInstrument(String& newId) {
    instrument->renameId(newId);
    return instrument->getId();
}
