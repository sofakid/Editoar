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

#ifndef JUCER_APPLICATION_H_INCLUDED
#define JUCER_APPLICATION_H_INCLUDED

#include "jucer_MainWindow.h"
#include "../Code Editor/jucer_SourceCodeEditor.h"
#include "../Utility/jucer_EditoarLookAndFeel.h"

//==============================================================================
class EditoarApplication   : public JUCEApplication,
                              private Timer,
                              private AsyncUpdater
{
public:
    EditoarApplication();

    static EditoarApplication& getApp();
    static ApplicationCommandManager& getCommandManager();

    //==============================================================================
    void initialise (const String& commandLine) override;
    void initialiseBasics();
    bool initialiseLogger (const char* filePrefix);
    void initialiseWindows (const String& commandLine);

    void shutdown() override;
    void systemRequestedQuit() override;
    void deleteLogger();

    //==============================================================================
    const String getApplicationName() override       { return "Editoar"; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }

    String getVersionDescription() const;
    bool moreThanOneInstanceAllowed() override       { return true; } // this is handled manually in initialise()

    void anotherInstanceStarted (const String& commandLine) override;

    //==============================================================================
    MenuBarModel* getMenuModel();
    StringArray getMenuNames();
    void createMenu (PopupMenu&, const String& menuName);
    void createFileMenu (PopupMenu&);
    void createEditMenu (PopupMenu&);
    void createViewMenu (PopupMenu&);
    void createColourSchemeItems (PopupMenu&);
    void createWindowMenu (PopupMenu&);
    void createExtraAppleMenuItems (PopupMenu&);
    void handleMainMenuCommand (int menuItemID);

    //==============================================================================
    void getAllCommands (Array<CommandID>&) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo&) override;
    bool perform (const InvocationInfo&) override;

    //==============================================================================
    void createNewProject();
    void updateNewlyOpenedProject (Project&);
    void askUserToOpenFile();
    bool openFile (const File&);
    bool closeAllDocuments (bool askUserToSave);
    bool closeAllMainWindows();

    PropertiesFile::Options getPropertyFileOptionsFor (const String& filename);

    //==============================================================================
    EditoarLookAndFeel lookAndFeel;

    ScopedPointer<StoredSettings> settings;
    ScopedPointer<Icons> icons;

    struct MainMenuModel;
    ScopedPointer<MainMenuModel> menuModel;

    MainWindowList mainWindowList;
    OpenDocumentManager openDocumentManager;
    ScopedPointer<ApplicationCommandManager> commandManager;

    ScopedPointer<Component> appearanceEditorWindow, globalPreferencesWindow;
    ScopedPointer<FileLogger> logger;

    bool isRunningCommandLine;

private:
    void* server = nullptr;

    bool checkEULA();
    bool currentEULAHasBeenAcceptedPreviously() const;
    String getEULAChecksumProperty() const;
    void setCurrentEULAAccepted (bool hasBeenAccepted) const;

	void timerCallback() override {};
    void handleAsyncUpdate() override;
    void initCommandManager();
};


#endif   // JUCER_APPLICATION_H_INCLUDED
