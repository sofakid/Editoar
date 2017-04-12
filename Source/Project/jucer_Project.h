/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef JUCER_PROJECT_H_INCLUDED
#define JUCER_PROJECT_H_INCLUDED

class ProjectType;

//==============================================================================
class Project  : public FileBasedDocument,
                 public ValueTree::Listener
{
public:
    //==============================================================================
    Project (const File&);
    ~Project();

    //==============================================================================
    // FileBasedDocument stuff..
    String getDocumentTitle() override;
    Result loadDocument (const File& file) override;
    Result saveDocument (const File& file) override;
    Result saveProject (const File& file, bool isCommandLineApp);
    Result saveResourcesOnly (const File& file);
    File getLastDocumentOpened() override;
    void setLastDocumentOpened (const File& file) override;

    void setTitle (const String& newTitle);

    //==============================================================================
    File getProjectFolder() const                       { return getFile().getParentDirectory(); }
    ValueTree getProjectRoot() const                    { return projectRoot; }
    String getTitle() const;
    Value getProjectNameValue()                         { return getMainGroup().getNameValue(); }
    String getProjectFilenameRoot()                     { return File::createLegalFileName (getDocumentTitle()); }
    String getProjectUID() const                        { return projectRoot [Ids::ID]; }

    //==============================================================================
    template <class FileType>
    bool shouldBeAddedToBinaryResourcesByDefault (const FileType& file)
    {
        return ! file.hasFileExtension (sourceOrHeaderFileExtensions);
    }

    File resolveFilename (String filename) const;
    String getRelativePathForFile (const File& file) const;

    //==============================================================================
    // Creates editors for the project settings
    void createPropertyEditors (PropertyListBuilder&);

    //==============================================================================
    // project types
    const ProjectType& getProjectType() const;
    Value getProjectTypeValue()                         { return getProjectValue (Ids::projectType); }
    String getProjectTypeString() const                 { return projectRoot [Ids::projectType]; }

    Value getVersionValue()                             { return getProjectValue (Ids::version); }
    String getVersionString() const                     { return projectRoot [Ids::version]; }
    String getVersionAsHex() const;
    int getVersionAsHexInteger() const;

    Value getBundleIdentifier()                         { return getProjectValue (Ids::bundleIdentifier); }
    String getDefaultBundleIdentifier()                 { return "com.yourcompany." + CodeHelpers::makeValidIdentifier (getTitle(), false, true, false); }

    Value getCompanyName()                              { return getProjectValue (Ids::companyName); }
    Value getCompanyWebsite()                           { return getProjectValue (Ids::companyWebsite); }
    Value getCompanyEmail()                             { return getProjectValue (Ids::companyEmail); }

    //==============================================================================
    Value getProjectValue (const Identifier& name)      { return projectRoot.getPropertyAsValue (name, getUndoManagerFor (projectRoot)); }

    Value getProjectPreprocessorDefs()                  { return getProjectValue (Ids::defines); }
    StringPairArray getPreprocessorDefs() const;

    Value getProjectUserNotes()                         { return getProjectValue (Ids::userNotes); }

    //==============================================================================
    File getGeneratedCodeFolder() const                         { return getFile().getSiblingFile ("JuceLibraryCode"); }
    File getSourceFilesFolder() const                           { return getProjectFolder().getChildFile ("Source"); }
    File getLocalModulesFolder() const                          { return getGeneratedCodeFolder().getChildFile ("modules"); }
    File getLocalModuleFolder (const String& moduleID) const    { return getLocalModulesFolder().getChildFile (moduleID); }
    File getAppIncludeFile() const                              { return getGeneratedCodeFolder().getChildFile (getJuceSourceHFilename()); }

    File getBinaryDataCppFile (int index) const;
    File getBinaryDataHeaderFile() const                { return getBinaryDataCppFile (0).withFileExtension (".h"); }
    Value getMaxBinaryFileSize()                        { return getProjectValue (Ids::maxBinaryFileSize); }
    Value shouldIncludeBinaryInAppConfig()              { return getProjectValue (Ids::includeBinaryInAppConfig); }
    Value binaryDataNamespace()                         { return getProjectValue (Ids::binaryDataNamespace); }

    //==============================================================================
    String getAppConfigFilename() const                 { return "AppConfig.h"; }
    String getJuceSourceFilenameRoot() const            { return "JuceLibraryCode"; }
    String getJuceSourceHFilename() const               { return "JuceHeader.h"; }

    void updateDeprecatedProjectSettingsInteractively();

    //==============================================================================
    class Item
    {
    public:
        //==============================================================================
        Item (Project& project, const ValueTree& itemNode);
        Item (const Item& other);

        static Item createGroup (Project& project, const String& name, const String& uid);
        void initialiseMissingProperties();

        //==============================================================================
        bool isValid() const                            { return state.isValid(); }
        bool operator== (const Item& other) const       { return state == other.state && &project == &other.project; }
        bool operator!= (const Item& other) const       { return ! operator== (other); }

        //==============================================================================
        bool isFile() const;
        bool isGroup() const;
        bool isMainGroup() const;
        bool isImageFile() const;
        bool isSoundFile() const;

        String getID() const;
        void setID (const String& newID);
        Item findItemWithID (const String& targetId) const; // (recursive search)

        Drawable* loadAsImageFile() const;

        //==============================================================================
        Value getNameValue();
        String getName() const;
        File getFile() const;
        String getFilePath() const;
        void setFile (const File& file);
        void setFile (const RelativePath& file);
        File determineGroupFolder() const;
        bool renameFile (const File& newFile);

        bool shouldBeAddedToTargetProject() const;
        
        //==============================================================================
        bool canContain (const Item& child) const;
        int getNumChildren() const                      { return state.getNumChildren(); }
        Item getChild (int index) const                 { return Item (project, state.getChild (index)); }

        Item addNewSubGroup (const String& name, int insertIndex);
        Item getOrCreateSubGroup (const String& name);
        void addChild (const Item& newChild, int insertIndex);
        bool addFileAtIndex (const File& file, int insertIndex, bool shouldCompile);
        bool addFileRetainingSortOrder (const File& file, bool shouldCompile);
        void addFileUnchecked (const File& file, int insertIndex, bool shouldCompile);
        bool addRelativeFile (const RelativePath& file, int insertIndex, bool shouldCompile);
        void removeItemFromProject();
        void sortAlphabetically (bool keepGroupsAtStart, bool recursive);
        Item findItemForFile (const File& file) const;
        bool containsChildForFile (const RelativePath& file) const;

        Item getParent() const;
        Item createCopy();

        UndoManager* getUndoManager() const              { return project.getUndoManagerFor (state); }

        Icon getIcon() const;
        bool isIconCrossedOut() const;

        Project& project;
        ValueTree state;

    private:
        Item& operator= (const Item&);
    };

    Item getMainGroup();
    Item getUnitTestsGroup();

    void findAllImageItems (OwnedArray<Item>& items);

    //==============================================================================
    struct ConfigFlag
    {
        String symbol, description, sourceModuleID, defaultValue;
        Value value;   // 1 = true, 2 = false, anything else = use default
    };

    static const char* const configFlagDefault;
    static const char* const configFlagEnabled;
    static const char* const configFlagDisabled;

    Value getConfigFlag (const String& name);
    bool isConfigFlagEnabled (const String& name) const;

    //==============================================================================
    String getFileTemplate (const String& templateName);

    //==============================================================================
    PropertiesFile& getStoredProperties() const;

    //==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;

    //==============================================================================
    UndoManager* getUndoManagerFor (const ValueTree&) const             { return nullptr; }

    //==============================================================================
    static const char* projectFileExtension;

    //==============================================================================
    bool hasProjectBeenModified();
    void updateModificationTime() { modificationTime = getFile().getLastModificationTime(); }

private:
    //==============================================================================
    friend class Item;
    ValueTree projectRoot;
    bool isSaving;

    void updateProjectSettings();
    void sanitiseConfigFlags();
    void setMissingDefaultValues();
    ValueTree getConfigNode();

    Time modificationTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project)
};


#endif   // JUCER_PROJECT_H_INCLUDED
