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

#include "../Code Editor/SkoarCodeEditor.hpp"

//==============================================================================
struct EditoarApplication::MainMenuModel  : public MenuBarModel
{
    MainMenuModel()
    {
        setApplicationCommandManagerToWatch (&getCommandManager());
    }

    StringArray getMenuBarNames() override
    {
        return getApp().getMenuNames();
    }

    PopupMenu getMenuForIndex (int /*topLevelMenuIndex*/, const String& menuName) override
    {
        PopupMenu menu;
        getApp().createMenu (menu, menuName);
        return menu;
    }

    void menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/) override
    {
        getApp().handleMainMenuCommand (menuItemID);
    }
};

//==============================================================================
EditoarApplication::EditoarApplication() :  isRunningCommandLine (false)
{
}

void EditoarApplication::initialise (const String& commandLine)
{
    if (commandLine.trimStart().startsWith ("--server"))
    {
        initialiseLogger ("Compiler_Log_");
        LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);

       #if JUCE_MAC
        Process::setDockIconVisible (false);
       #endif

    }
    else
    {
        initialiseLogger ("IDE_Log_");
        Logger::writeToLog (SystemStats::getOperatingSystemName());
        Logger::writeToLog ("CPU: " + String (SystemStats::getCpuSpeedInMegaherz())
                              + "MHz  Cores: " + String (SystemStats::getNumCpus())
                              + "  " + String (SystemStats::getMemorySizeInMegabytes()) + "MB");

        initialiseBasics();

        if (commandLine.isNotEmpty())
        {
            isRunningCommandLine = true;
            const int appReturnCode = performCommandLine (commandLine);

            if (appReturnCode != commandLineNotPerformed)
            {
                setApplicationReturnValue (appReturnCode);
                quit();
                return;
            }

            isRunningCommandLine = false;
        }

        if (sendCommandLineToPreexistingInstance())
        {
            DBG ("Another instance is running - quitting...");
            quit();
            return;
        }

        //openDocumentManager.registerType (new EditoarAppClasses::LiveBuildCodeEditorDocument::Type(), 2);

        if (! checkEULA())
        {
            quit();
            return;
        }

        initCommandManager();
        menuModel = new MainMenuModel();

        settings->appearance.refreshPresetSchemeList();

        // do further initialisation in a moment when the message loop has started
        triggerAsyncUpdate();
    }
}

void EditoarApplication::initialiseBasics()
{
    LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    settings = new StoredSettings();
    ImageCache::setCacheTimeout (30 * 1000);
    icons = new Icons();
}

bool EditoarApplication::initialiseLogger (const char* filePrefix)
{
    if (logger == nullptr)
    {
       #if JUCE_LINUX
        String folder = "~/.config/Editoar/Logs";
       #else
        String folder = "org.skoarcery.editoar";
       #endif

        logger = FileLogger::createDateStampedLogger (folder, filePrefix, ".txt",
                                                      getApplicationName() + " " + getApplicationVersion()
                                                        + "  ---  Build date: " __DATE__);
        Logger::setCurrentLogger (logger);
    }

    return logger != nullptr;
}

void EditoarApplication::handleAsyncUpdate()
{
    initialiseWindows (getCommandLineParameters());

   #if JUCE_MAC
    PopupMenu extraAppleMenuItems;
    createExtraAppleMenuItems (extraAppleMenuItems);

    // workaround broken "Open Recent" submenu: not passing the
    // submenu's title here avoids the defect in JuceMainMenuHandler::addMenuItem
    MenuBarModel::setMacMainMenu (menuModel, &extraAppleMenuItems); //, "Open Recent");
   #endif

}

void EditoarApplication::initialiseWindows (const String& commandLine)
{
    const String commandLineWithoutNSDebug (commandLine.replace ("-NSDocumentRevisionsDebugMode YES", StringRef()));

    if (commandLineWithoutNSDebug.trim().isNotEmpty() && ! commandLineWithoutNSDebug.trim().startsWithChar ('-'))
        anotherInstanceStarted (commandLine);
    else
        mainWindowList.reopenLastProjects();

    mainWindowList.createWindowIfNoneAreOpen();
}

void EditoarApplication::shutdown()
{
    appearanceEditorWindow = nullptr;
    globalPreferencesWindow = nullptr;
    
    mainWindowList.forceCloseAllWindows();
    openDocumentManager.clear();

   #if JUCE_MAC
    MenuBarModel::setMacMainMenu (nullptr);
   #endif

    menuModel = nullptr;
    commandManager = nullptr;
    settings = nullptr;

    LookAndFeel::setDefaultLookAndFeel (nullptr);

    if (! isRunningCommandLine)
        Logger::writeToLog ("Shutdown");

    deleteLogger();
}

struct AsyncQuitRetrier  : private Timer
{
    AsyncQuitRetrier()   { startTimer (500); }

    void timerCallback() override
    {
        stopTimer();
        delete this;

        if (JUCEApplicationBase* app = JUCEApplicationBase::getInstance())
            app->systemRequestedQuit();
    }

    JUCE_DECLARE_NON_COPYABLE (AsyncQuitRetrier)
};

void EditoarApplication::systemRequestedQuit()
{
    if (ModalComponentManager::getInstance()->cancelAllModalComponents())
    {
        new AsyncQuitRetrier();
    }
    else
    {
        if (closeAllMainWindows())
            quit();
    }
}

//==============================================================================
String EditoarApplication::getVersionDescription() const
{
    String s;

    const Time buildDate (Time::getCompilationDate());

    s << "Editoar " << ProjectInfo::versionString
      << newLine
      << "Build date: " << buildDate.getDayOfMonth()
      << " " << Time::getMonthName (buildDate.getMonth(), true)
      << " " << buildDate.getYear();

    return s;
}

void EditoarApplication::anotherInstanceStarted (const String& commandLine)
{
    if (server == nullptr && ! commandLine.trim().startsWithChar ('-'))
        openFile (File (commandLine.unquoted()));
}

EditoarApplication& EditoarApplication::getApp()
{
    EditoarApplication* const app = dynamic_cast<EditoarApplication*> (JUCEApplication::getInstance());
    jassert (app != nullptr);
    return *app;
}

ApplicationCommandManager& EditoarApplication::getCommandManager()
{
    ApplicationCommandManager* cm = EditoarApplication::getApp().commandManager;
    jassert (cm != nullptr);
    return *cm;
}


//==============================================================================
enum
{
    recentProjectsBaseID = 100,
    activeDocumentsBaseID = 300,
    colourSchemeBaseID = 1000
};

MenuBarModel* EditoarApplication::getMenuModel()
{
  return menuModel.get();
}

StringArray EditoarApplication::getMenuNames()
{
    const char* const names[] = { "File", "Edit", "View", "Window", nullptr };
    return StringArray (names);
}

void EditoarApplication::createMenu (PopupMenu& menu, const String& menuName)
{
    if (menuName == "File")             createFileMenu   (menu);
    else if (menuName == "Edit")        createEditMenu   (menu);
    else if (menuName == "View")        createViewMenu   (menu);
    else if (menuName == "Window")      createWindowMenu (menu);
    else                                jassertfalse; // names have changed?
}

void EditoarApplication::createFileMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::newProject);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::open);

    PopupMenu recentFiles;
    settings->recentFiles.createPopupMenuItems (recentFiles, recentProjectsBaseID, true, true);
    menu.addSubMenu ("Open Recent", recentFiles);

    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::closeDocument);
    menu.addCommandItem (commandManager, CommandIDs::saveDocument);
    menu.addCommandItem (commandManager, CommandIDs::saveDocumentAs);
    menu.addCommandItem (commandManager, CommandIDs::saveAll);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::closeProject);
    menu.addCommandItem (commandManager, CommandIDs::saveProject);
    menu.addSeparator();
   
    #if ! JUCE_MAC
      menu.addCommandItem (commandManager, CommandIDs::showGlobalPreferences);
      menu.addSeparator();
      menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    #endif
}

void EditoarApplication::createEditMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::undo);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::redo);
    menu.addSeparator();
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::cut);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::copy);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::paste);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::del);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::selectAll);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::deselectAll);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::showFindPanel);
    menu.addCommandItem (commandManager, CommandIDs::findSelection);
    menu.addCommandItem (commandManager, CommandIDs::findNext);
    menu.addCommandItem (commandManager, CommandIDs::findPrevious);
}

void EditoarApplication::createViewMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::showFilePanel);
    menu.addCommandItem (commandManager, CommandIDs::showConfigPanel);
    menu.addCommandItem (commandManager, CommandIDs::showProjectSettings);
    menu.addSeparator();
    createColourSchemeItems (menu);
}

void EditoarApplication::createColourSchemeItems (PopupMenu& menu)
{
    const StringArray presetSchemes (settings->appearance.getPresetSchemes());

    if (presetSchemes.size() > 0)
    {
        PopupMenu schemes;

        for (int i = 0; i < presetSchemes.size(); ++i)
            schemes.addItem (colourSchemeBaseID + i, presetSchemes[i]);

        menu.addSubMenu ("Colour Scheme", schemes);
    }
}

void EditoarApplication::createWindowMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::closeWindow);
    menu.addSeparator();

    menu.addCommandItem (commandManager, CommandIDs::goToPreviousDoc);
    menu.addCommandItem (commandManager, CommandIDs::goToNextDoc);
    menu.addCommandItem (commandManager, CommandIDs::goToCounterpart);
    menu.addSeparator();

    const int numDocs = jmin (50, openDocumentManager.getNumOpenDocuments());

    for (int i = 0; i < numDocs; ++i)
    {
        OpenDocumentManager::Document* doc = openDocumentManager.getOpenDocument(i);
        menu.addItem (activeDocumentsBaseID + i, doc->getName());
    }

    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::closeAllDocuments);
}

void EditoarApplication::createExtraAppleMenuItems (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::showGlobalPreferences);
}

void EditoarApplication::handleMainMenuCommand (int menuItemID)
{
    if (menuItemID >= recentProjectsBaseID && menuItemID < recentProjectsBaseID + 100)
    {
        // open a file from the "recent files" menu
        openFile (settings->recentFiles.getFile (menuItemID - recentProjectsBaseID));
    }
    else if (menuItemID >= activeDocumentsBaseID && menuItemID < activeDocumentsBaseID + 200)
    {
        if (OpenDocumentManager::Document* doc = openDocumentManager.getOpenDocument (menuItemID - activeDocumentsBaseID))
            mainWindowList.openDocument (doc, true);
        else
            jassertfalse;
    }
    else if (menuItemID >= colourSchemeBaseID && menuItemID < colourSchemeBaseID + 200)
    {
        settings->appearance.selectPresetScheme (menuItemID - colourSchemeBaseID);
    }
    
}

//==============================================================================
void EditoarApplication::getAllCommands (Array <CommandID>& commands)
{
    JUCEApplication::getAllCommands (commands);

    const CommandID ids[] = { CommandIDs::newProject,
                              CommandIDs::open,
                              CommandIDs::closeAllDocuments,
                              CommandIDs::saveAll,
                              CommandIDs::showGlobalPreferences};

    commands.addArray (ids, numElementsInArray (ids));
}

void EditoarApplication::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
    case CommandIDs::newProject:
        result.setInfo ("New Project...", "Creates a new Jucer project", CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress ('n', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::open:
        result.setInfo ("Open...", "Opens a Jucer project", CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress ('o', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::showGlobalPreferences:
        result.setInfo ("Preferences...", "Shows the preferences window.", CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress (',', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::closeAllDocuments:
        result.setInfo ("Close All Documents", "Closes all open documents", CommandCategories::general, 0);
        result.setActive (openDocumentManager.getNumOpenDocuments() > 0);
        break;

    case CommandIDs::saveAll:
        result.setInfo ("Save All", "Saves all open documents", CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress ('s', ModifierKeys::commandModifier | ModifierKeys::altModifier, 0));
        break;

    default:
        JUCEApplication::getCommandInfo (commandID, result);
        break;
    }
}

bool EditoarApplication::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::newProject:                createNewProject(); break;
        case CommandIDs::open:                      askUserToOpenFile(); break;
        case CommandIDs::saveAll:                   openDocumentManager.saveAll(); break;
        case CommandIDs::closeAllDocuments:         closeAllDocuments (true); break;
        case CommandIDs::showGlobalPreferences:     AppearanceSettings::showGlobalPreferences (globalPreferencesWindow); break;
        default:                                    return JUCEApplication::perform (info);
    }

    return true;
}

//==============================================================================
void EditoarApplication::createNewProject()
{
    MainWindow* mw = mainWindowList.getOrCreateEmptyWindow();
    mw->showNewProjectWizard();
    mainWindowList.avoidSuperimposedWindows (mw);
}

void EditoarApplication::updateNewlyOpenedProject (Project&)
{
    // no op
}

void EditoarApplication::askUserToOpenFile()
{
    FileChooser fc ("Open File");

    if (fc.browseForFileToOpen())
        openFile (fc.getResult());
}

bool EditoarApplication::openFile (const File& file)
{
    return mainWindowList.openFile (file);
}

bool EditoarApplication::closeAllDocuments (bool askUserToSave)
{
    return openDocumentManager.closeAll (askUserToSave);
}

bool EditoarApplication::closeAllMainWindows()
{
    return server != nullptr || mainWindowList.askAllWindowsToClose();
}

//==============================================================================
struct FileWithTime
{
    FileWithTime (const File& f) : file (f), time (f.getLastModificationTime()) {}
    FileWithTime() {}

    bool operator<  (const FileWithTime& other) const    { return time <  other.time; }
    bool operator== (const FileWithTime& other) const    { return time == other.time; }

    File file;
    Time time;
};

void EditoarApplication::deleteLogger()
{
    const int maxNumLogFilesToKeep = 50;

    Logger::setCurrentLogger (nullptr);

    if (logger != nullptr)
    {
        Array<File> logFiles;
        logger->getLogFile().getParentDirectory().findChildFiles (logFiles, File::findFiles, false);

        if (logFiles.size() > maxNumLogFilesToKeep)
        {
            Array <FileWithTime> files;

            for (int i = 0; i < logFiles.size(); ++i)
                files.addUsingDefaultSort (logFiles.getReference(i));

            for (int i = 0; i < files.size() - maxNumLogFilesToKeep; ++i)
                files.getReference(i).file.deleteFile();
        }
    }

    logger = nullptr;
}

PropertiesFile::Options EditoarApplication::getPropertyFileOptionsFor (const String& filename)
{
    PropertiesFile::Options options;
    options.applicationName     = filename;
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Application Support";
   #if JUCE_LINUX
    options.folderName          = "~/.config/Editoar";
   #else
    options.folderName          = "Editoar";
   #endif

    return options;
}

//==============================================================================

bool EditoarApplication::checkEULA()
{
    if (currentEULAHasBeenAcceptedPreviously())
        return true;

    ScopedPointer<AlertWindow> eulaDialogue (new EULADialogue());
    bool hasBeenAccepted = (eulaDialogue->runModalLoop() == EULADialogue::accepted);
    setCurrentEULAAccepted (hasBeenAccepted);
    return hasBeenAccepted;
}

bool EditoarApplication::currentEULAHasBeenAcceptedPreviously() const
{
    return getGlobalProperties().getValue (getEULAChecksumProperty()).getIntValue() != 0;
}

String EditoarApplication::getEULAChecksumProperty() const
{
    return "eulaChecksum_" + MD5 (BinaryData::editoar_EULA_txt,
                                  BinaryData::editoar_EULA_txtSize).toHexString();
}

void EditoarApplication::setCurrentEULAAccepted (bool hasBeenAccepted) const
{
    const String checksum (getEULAChecksumProperty());
    auto& globals = getGlobalProperties();

    if (hasBeenAccepted)
        globals.setValue (checksum, 1);
    else
        globals.removeValue (checksum);

    globals.saveIfNeeded();
}

void EditoarApplication::initCommandManager()
{
    commandManager = new ApplicationCommandManager();
    commandManager->registerAllCommandsForTarget (this);

    {
        CodeDocument doc;
        SkoarCodeEditorComponent ed (File(), doc);
        commandManager->registerAllCommandsForTarget (&ed);
    }

}
