#pragma once

#include "../jucer_Headers.h"
#include "../Application/jucer_Application.h"
#include "../Project/jucer_Project.h"
#include "../Application/jucer_OpenDocumentManager.h"
#include "../Skoarish/Instrument.h"

//==============================================================================
class SoundFileDocument : public OpenDocumentManager::Document
{
public:
    SoundFileDocument(Project* p, const File& f);

    //==============================================================================
    struct Type : public OpenDocumentManager::DocumentType
    {
        bool canOpenFile(const File& file) override;
        Document* openFile(Project* p, const File& file) override;
    };

    // === overrides ==========================================================================
    bool loadedOk() const override;
    bool isForFile(const File& f) const override;
    bool isForNode(const ValueTree&) const override;
    bool refersToProject(Project& p) const override;
    Project* getProject() const override;
    bool needsSaving() const override;
    bool save() override;
    bool saveAs() override;
    bool hasFileBeenModifiedExternally() override;
    void reloadFromFile() override;
    String getName() const override;
    File getFile() const override;
    Component* createEditor() override;
    Component* createViewer() override;
    void fileHasBeenRenamed(const File& newFile) override;
    String getState() const override;
    void restoreState(const String&) override;
    String getType() const override;

    // === customs ===========================================================================
    SkoarishInstrument* getInstrument();
    String renameInstrument(String&);
    
private:

    Project* const project;
    File file;
    Time fileModificationTime;

    String name;

    SkoarishInstrument *instrument;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundFileDocument)
};

