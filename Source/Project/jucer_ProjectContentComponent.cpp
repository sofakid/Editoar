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

#include "../jucer_Headers.h"
#include "jucer_ProjectContentComponent.h"
#include "../Application/jucer_MainWindow.h"
#include "../Application/jucer_Application.h"
#include "../Code Editor/jucer_SourceCodeEditor.h"
#include "../Utility/jucer_FilePathPropertyComponent.h"
#include "jucer_TreeItemTypes.h"
#include "../Testoar/TestoarTreeItemTypes.h"
#include "../Testoar/Testoar.h"

#include "../Debuggoar/DebuggoarComponent.h"
#include "../Debuggoar/SkoarASTComponent.h"
#include "../Debuggoar/SkoarProjectionComponent.h"



//==============================================================================
class FileTreePanel   : public TreePanelBase
{
public:
    FileTreePanel (Project& p)
        : TreePanelBase (&p, "fileTreeState")
    {
        tree.setMultiSelectEnabled (true);
        setRoot (new FileTreeItemTypes::GroupItem (p.getMainGroup()));
        tree.setRootItemVisible(false);
    }

    void updateMissingFileStatuses()
    {
        if (FileTreeItemTypes::ProjectTreeItemBase* p = dynamic_cast<FileTreeItemTypes::ProjectTreeItemBase*> (rootItem.get()))
            p->checkFileStatus();
    }
};

//==============================================================================
class ConfigTreePanel   : public TreePanelBase
{
public:
    ConfigTreePanel (Project& p)
        : TreePanelBase (&p, "settingsTreeState")
    {
        tree.setMultiSelectEnabled (false);
        setRoot (new ConfigTreeItemTypes::RootItem (p));

        if (tree.getNumSelectedItems() == 0)
            tree.getRootItem()->setSelected (true, true);

    }

    void resized() override
    {
        Rectangle<int> r (getAvailableBounds());
        r.removeFromBottom (6);

        if (createExporterButton.isVisible())
        {
            r.removeFromBottom (10);
            createExporterButton.setBounds (r.removeFromBottom (30).reduced (16, 4));
        }

        tree.setBounds (r);
    }

    static void reselect (TreeViewItem& item)
    {
        item.setSelected (false, true);
        item.setSelected (true, true);
    }

    void showProjectSettings()
    {
        if (ConfigTreeItemTypes::ConfigTreeItemBase* root = dynamic_cast<ConfigTreeItemTypes::ConfigTreeItemBase*> (rootItem.get()))
            if (root->isProjectSettings())
                reselect (*root);
    }

    TextButton createExporterButton;
};


//==============================================================================
class TestoarTreePanel : public TreePanelBase
{
public:
    TestoarTreePanel(Project& p)
        : TreePanelBase(&p, "settingsTreeState")
    {
        Testoar::initialize();

        tree.setMultiSelectEnabled(false);
        setRoot(new TestoarTreeItemTypes::RootItem());
        tree.setRootItemVisible(false);
        tree.setDefaultOpenness(false);

        if (tree.getNumSelectedItems() == 0)
            tree.getRootItem()->setSelected(true, true);

    }

    void resized() override
    {
        Rectangle<int> r(getAvailableBounds());
        r.removeFromBottom(6);

        if (runAllButton.isVisible())
        {
            r.removeFromBottom(10);
            runAllButton.setBounds(r.removeFromTop(30).reduced(16, 4));
        }

        tree.setBounds(r);
    }

    static void reselect(TreeViewItem& item)
    {
        item.setSelected(false, true);
        item.setSelected(true, true);
    }

    void showProjectSettings()
    {
        if (TestoarTreeItemTypes::TestoarTreeItemBase* root = dynamic_cast<TestoarTreeItemTypes::TestoarTreeItemBase*> (rootItem.get()))
            if (root->isProjectSettings())
                reselect(*root);
    }

    TextButton runAllButton;
};


//==============================================================================
struct LogoComponent  : public Component
{
    LogoComponent()
    {
        logo = Drawable::createFromImageData (BinaryData::skoar_logo_png, BinaryData::skoar_logo_pngSize);
    }

    void paint (Graphics& g) override
    {
        g.setColour (findColour (mainBackgroundColourId).contrasting (0.3f));

        Rectangle<int> r (getLocalBounds());

        g.setFont (15.0f);
        g.drawFittedText (getVersionInfo(), r.removeFromBottom (50), Justification::centredBottom, 3);

        logo->drawWithin (g, r.withTrimmedBottom (r.getHeight() / 4).toFloat(),
                          RectanglePlacement (RectanglePlacement::centred), 1.0f);
    }

    static String getVersionInfo()
    {
        return SystemStats::getJUCEVersion()
                + newLine
                + EditoarApplication::getApp().getVersionDescription();
    }

    ScopedPointer<Drawable> logo;
};

//==============================================================================
ProjectContentComponent::ProjectContentComponent()
    : project (nullptr),
      currentDocument (nullptr),
      treeViewTabs (TabbedButtonBar::TabsAtTop),
      bottomPanelComponent ()
{
    setOpaque (true);
    setWantsKeyboardFocus (true);

    addAndMakeVisible (logo = new LogoComponent());
      
    // -- bottom panel ----
    bottomPanelSizeConstrainer.setMinimumHeight(24);
    bottomPanelSizeConstrainer.setMaximumHeight(getHeight() - 50);
    
    addAndMakeVisible(bottomPanelComponent = new BottomPanelComponent());
    bottomPanelComponent->setBounds(0,0,300,500);

    addAndMakeVisible(resizerBarHoriz = new ResizableEdgeComponent(&*bottomPanelComponent, &bottomPanelSizeConstrainer,
        ResizableEdgeComponent::topEdge));
    resizerBarHoriz->setAlwaysOnTop(true);

    // -- file tree ---- 
    treeSizeConstrainer.setMinimumWidth (200);
    treeSizeConstrainer.setMaximumWidth (500);

    treeViewTabs.setOutline (0);
    treeViewTabs.getTabbedButtonBar().setMinimumTabScaleFactor (0.3);


    EditoarApplication::getApp().openDocumentManager.addListener (this);

    //Desktop::getInstance().addFocusChangeListener (this);
    startTimer (1600);
}

ProjectContentComponent::~ProjectContentComponent()
{
    //Desktop::getInstance().removeFocusChangeListener (this);

    EditoarApplication::getApp().openDocumentManager.removeListener (this);

    logo = nullptr;
    setProject (nullptr);
    contentView = nullptr;
    removeChildComponent (&bubbleMessage);
    removeChildComponent (bottomPanelComponent);
    resizerBarHoriz = nullptr;

    jassert (getNumChildComponents() <= 1);
}

void ProjectContentComponent::paint (Graphics& g)
{
    EditoarLookAndFeel::fillWithBackgroundTexture (*this, g);
}

void ProjectContentComponent::paintOverChildren (Graphics& g)
{
    if (resizerBar != nullptr)
    {
        const int shadowSize = 15;
        const int x = resizerBar->getX();

        const int y = 0;

        ColourGradient cg (Colours::black.withAlpha (0.25f), (float) x, 0,
                           Colours::transparentBlack,        (float) (x - shadowSize), 0, false);
        cg.addColour (0.4, Colours::black.withAlpha (0.07f));
        cg.addColour (0.6, Colours::black.withAlpha (0.02f));

        g.setGradientFill (cg);
        g.fillRect (x - shadowSize, y, shadowSize, treeViewTabs.getHeight());
    }
}

void ProjectContentComponent::resized()
{
    Rectangle<int> r(getLocalBounds());

    bottomPanelSizeConstrainer.setMaximumHeight(getHeight() - 50);

    bottomPanelComponent->setBounds (r.removeFromBottom (bottomPanelComponent->getHeight()));

    if (resizerBarHoriz != nullptr)
        resizerBarHoriz->setBounds(r.withY (r.getBottom()).withHeight (4));

    if (treeViewTabs.isVisible())
        treeViewTabs.setBounds (r.removeFromLeft (treeViewTabs.getWidth()));

    if (resizerBar != nullptr)
        resizerBar->setBounds (r.withWidth (4));

    if (contentView != nullptr)
        contentView->setBounds (r);

    if (logo != nullptr)
        logo->setBounds (r.reduced (r.getWidth() / 4, r.getHeight() / 4));
}

void ProjectContentComponent::lookAndFeelChanged()
{
    repaint();
}

void ProjectContentComponent::childBoundsChanged (Component* child)
{
    if (child == &treeViewTabs || child == bottomPanelComponent)
        resized();
}

void ProjectContentComponent::setProject (Project* newProject)
{
    if (project != newProject)
    {
        lastCrashMessage = String();

        if (project != nullptr)
            project->removeChangeListener (this);

        contentView = nullptr;
        resizerBar = nullptr;

        deleteProjectTabs();
        project = newProject;
        rebuildProjectTabs();
    }
}

void ProjectContentComponent::rebuildProjectTabs()
{
    deleteProjectTabs();

    if (project != nullptr)
    {
        addAndMakeVisible (treeViewTabs);

        createProjectTabs();

        PropertiesFile& settings = project->getStoredProperties();

        const String lastTabName (settings.getValue ("lastTab"));
        int lastTabIndex = treeViewTabs.getTabNames().indexOf (lastTabName);

        if (lastTabIndex < 0 || lastTabIndex > treeViewTabs.getNumTabs())
            lastTabIndex = 1;

        treeViewTabs.setCurrentTabIndex (lastTabIndex);

        int lastTreeWidth = settings.getValue ("projectPanelWidth").getIntValue();
        if (lastTreeWidth < 150)
            lastTreeWidth = 240;

        treeViewTabs.setBounds (0, 0, lastTreeWidth, getHeight());

        addAndMakeVisible (resizerBar = new ResizableEdgeComponent (&treeViewTabs, &treeSizeConstrainer,
                                                                    ResizableEdgeComponent::rightEdge));
        resizerBar->setAlwaysOnTop (true);

        project->addChangeListener (this);

        updateMissingFileStatuses();
    }
    else
    {
        treeViewTabs.setVisible (false);
    }

    resized();
}

void ProjectContentComponent::createProjectTabs()
{
    jassert (project != nullptr);
    const Colour tabColour (Colours::transparentBlack);

    treeViewTabs.addTab ("Files",  tabColour, new FileTreePanel (*project), true);
    //treeViewTabs.addTab ("Config", tabColour, new ConfigTreePanel (*project), true);
    treeViewTabs.addTab ("Testing", tabColour, new TestoarTreePanel(*project), true);
    treeViewTabs.addTab ("Trees", tabColour, new SkoarASTComponent(), true);
    treeViewTabs.addTab ("Projection", tabColour, new SkoarProjectionComponent (), true);


}

void ProjectContentComponent::deleteProjectTabs()
{
    if (project != nullptr && treeViewTabs.isShowing())
    {
        PropertiesFile& settings = project->getStoredProperties();

        if (treeViewTabs.getWidth() > 0)
            settings.setValue ("projectPanelWidth", treeViewTabs.getWidth());

        if (treeViewTabs.getNumTabs() > 0)
            settings.setValue ("lastTab", treeViewTabs.getCurrentTabName());
    }

    treeViewTabs.clearTabs();
}

void ProjectContentComponent::saveTreeViewState()
{
    for (int i = treeViewTabs.getNumTabs(); --i >= 0;)
        if (TreePanelBase* t = dynamic_cast<TreePanelBase*> (treeViewTabs.getTabContentComponent (i)))
            t->saveOpenness();
}

void ProjectContentComponent::saveOpenDocumentList()
{
    if (project != nullptr)
    {
        ScopedPointer<XmlElement> xml (recentDocumentList.createXML());

        if (xml != nullptr)
            project->getStoredProperties().setValue ("lastDocs", xml);
    }
}

void ProjectContentComponent::reloadLastOpenDocuments()
{
    if (project != nullptr)
    {
        ScopedPointer<XmlElement> xml (project->getStoredProperties().getXmlValue ("lastDocs"));

        if (xml != nullptr)
        {
            recentDocumentList.restoreFromXML (*project, *xml);
            showDocument (recentDocumentList.getCurrentDocument(), true);
        }
    }
}

bool ProjectContentComponent::documentAboutToClose (OpenDocumentManager::Document* document)
{
    hideDocument (document);
    return true;
}

void ProjectContentComponent::changeListenerCallback (ChangeBroadcaster*)
{
    updateMissingFileStatuses();
}

void ProjectContentComponent::updateMissingFileStatuses()
{
    if (FileTreePanel* tree = dynamic_cast<FileTreePanel*> (treeViewTabs.getTabContentComponent (0)))
        tree->updateMissingFileStatuses();
}

bool ProjectContentComponent::showEditorForFile (const File& f, bool grabFocus)
{
    return getCurrentFile() == f
            || showDocument (EditoarApplication::getApp().openDocumentManager.openFile (project, f), grabFocus);
}

bool ProjectContentComponent::hasFileInRecentList (const File& f) const
{
    return recentDocumentList.contains (f);
}

File ProjectContentComponent::getCurrentFile() const
{
    return currentDocument != nullptr ? currentDocument->getFile()
                                      : File();
}

bool ProjectContentComponent::showDocument (OpenDocumentManager::Document* doc, bool grabFocus)
{
    if (doc == nullptr)
        return false;

    if (doc->hasFileBeenModifiedExternally())
        doc->reloadFromFile();

    if (doc == getCurrentDocument() && contentView != nullptr)
    {
        if (grabFocus && contentView->isShowing () && contentView->isOnDesktop ())
            contentView->grabKeyboardFocus();

        return true;
    }

    recentDocumentList.newDocumentOpened (doc);

    bool opened = setEditorComponent (doc->createEditor(), doc);

    if (opened && grabFocus && contentView != nullptr && contentView->isShowing () && contentView->isOnDesktop ())
        contentView->grabKeyboardFocus();

    return opened;
}

void ProjectContentComponent::hideEditor()
{
    currentDocument = nullptr;
    contentView = nullptr;
    updateMainWindowTitle();
    EditoarApplication::getCommandManager().commandStatusChanged();
    resized();
}

void ProjectContentComponent::hideDocument (OpenDocumentManager::Document* doc)
{
    if (doc == currentDocument)
    {
        if (OpenDocumentManager::Document* replacement = recentDocumentList.getClosestPreviousDocOtherThan (doc))
            showDocument (replacement, true);
        else
            hideEditor();
    }
}

bool ProjectContentComponent::setEditorComponent (Component* editor,
                                                  OpenDocumentManager::Document* doc)
{
    if (editor != nullptr)
    {
        contentView = nullptr;
        currentDocument = doc;
        auto sourceEditor = dynamic_cast<SourceCodeEditor*>(editor);
        SkoarCodeEditorComponent* skoarEditor = nullptr;
        if (sourceEditor != nullptr) {
            skoarEditor = dynamic_cast<SkoarCodeEditorComponent*>(sourceEditor->editor.get());
        }
        
        if (skoarEditor != nullptr) {
            DebuggoarComponent *debuggoar = new DebuggoarComponent(skoarEditor, editor);
            contentView = debuggoar;
            addAndMakeVisible(debuggoar);
        }
        else {
            contentView = editor;
            addAndMakeVisible(editor);
        }
        resized();

        updateMainWindowTitle();
        EditoarApplication::getCommandManager().commandStatusChanged();
        return true;
    }

    updateMainWindowTitle();
    return false;
}

void ProjectContentComponent::closeDocument()
{
    if (currentDocument != nullptr)
        EditoarApplication::getApp().openDocumentManager.closeDocument (currentDocument, true);
    else if (contentView != nullptr)
        if (! goToPreviousFile())
            hideEditor();
}

static void showSaveWarning (OpenDocumentManager::Document* currentDocument)
{
    AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                 TRANS("Save failed!"),
                                 TRANS("Couldn't save the file:")
                                   + "\n" + currentDocument->getFile().getFullPathName());
}

void ProjectContentComponent::saveDocument()
{
    if (currentDocument != nullptr)
    {
        if (! currentDocument->save())
            showSaveWarning (currentDocument);
    }
    else
        saveProject();

    updateMainWindowTitle();
}

void ProjectContentComponent::saveAs()
{
    if (currentDocument != nullptr && ! currentDocument->saveAs())
        showSaveWarning (currentDocument);
}

bool ProjectContentComponent::goToPreviousFile()
{
    OpenDocumentManager::Document* doc = recentDocumentList.getCurrentDocument();

    if (doc == nullptr || doc == getCurrentDocument())
        doc = recentDocumentList.getPrevious();

    return showDocument (doc, true);
}

bool ProjectContentComponent::goToNextFile()
{
    return showDocument (recentDocumentList.getNext(), true);
}

bool ProjectContentComponent::canGoToCounterpart() const
{
    return currentDocument != nullptr
            && currentDocument->getCounterpartFile().exists();
}

bool ProjectContentComponent::goToCounterpart()
{
    if (currentDocument != nullptr)
    {
        const File file (currentDocument->getCounterpartFile());

        if (file.exists())
            return showEditorForFile (file, true);
    }

    return false;
}

bool ProjectContentComponent::saveProject()
{
    return project != nullptr
            && project->save (true, true) == FileBasedDocument::savedOk;
}

void ProjectContentComponent::closeProject()
{
    if (MainWindow* const mw = findParentComponentOfClass<MainWindow>())
        mw->closeCurrentProject();
}

void ProjectContentComponent::showFilesTab()
{
    treeViewTabs.setCurrentTabIndex (0);
}

void ProjectContentComponent::showConfigTab()
{
    treeViewTabs.setCurrentTabIndex (1);
}

void ProjectContentComponent::showProjectSettings()
{
    showConfigTab();

    if (ConfigTreePanel* const tree = dynamic_cast<ConfigTreePanel*> (treeViewTabs.getCurrentContentComponent()))
        tree->showProjectSettings();
}


void ProjectContentComponent::deleteSelectedTreeItems()
{
    if (TreePanelBase* const tree = dynamic_cast<TreePanelBase*> (treeViewTabs.getCurrentContentComponent()))
        tree->deleteSelectedItems();
}

void ProjectContentComponent::updateMainWindowTitle()
{
    if (MainWindow* mw = findParentComponentOfClass<MainWindow>())
    {
        String title;
        File file;
        bool edited = false;

        if (currentDocument != nullptr)
        {
            title = currentDocument->getName();
            edited = currentDocument->needsSaving();
            file = currentDocument->getFile();
        }

        if (ComponentPeer* peer = mw->getPeer())
        {
            if (! peer->setDocumentEditedStatus (edited))
                if (edited)
                    title << "*";

            peer->setRepresentedFile (file);
        }

        mw->updateTitle (title);
    }
}

void ProjectContentComponent::showBubbleMessage (Rectangle<int> pos, const String& text)
{
    addChildComponent (bubbleMessage);
    bubbleMessage.setColour (BubbleComponent::backgroundColourId, Colours::white.withAlpha (0.7f));
    bubbleMessage.setColour (BubbleComponent::outlineColourId, Colours::black.withAlpha (0.8f));
    bubbleMessage.setAlwaysOnTop (true);

    bubbleMessage.showAt (pos, AttributedString (text), 3000, true, false);
}

//==============================================================================
struct AsyncCommandRetrier  : public Timer
{
    AsyncCommandRetrier (const ApplicationCommandTarget::InvocationInfo& i)  : info (i)
    {
        info.originatingComponent = nullptr;
        startTimer (500);
    }

    void timerCallback() override
    {
        stopTimer();
        EditoarApplication::getCommandManager().invoke (info, true);
        delete this;
    }

    ApplicationCommandTarget::InvocationInfo info;

    JUCE_DECLARE_NON_COPYABLE (AsyncCommandRetrier)
};

bool reinvokeCommandAfterCancellingModalComps (const ApplicationCommandTarget::InvocationInfo& info)
{
    if (ModalComponentManager::getInstance()->cancelAllModalComponents())
    {
        new AsyncCommandRetrier (info);
        return true;
    }

    return false;
}

//==============================================================================
ApplicationCommandTarget* ProjectContentComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void ProjectContentComponent::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = { CommandIDs::saveDocument,
                              CommandIDs::saveDocumentAs,
                              CommandIDs::closeDocument,
                              CommandIDs::saveProject,
                              CommandIDs::closeProject,
                              CommandIDs::showFilePanel,
                              CommandIDs::showConfigPanel,
                              CommandIDs::showProjectSettings,
                              CommandIDs::goToPreviousDoc,
                              CommandIDs::goToNextDoc,
                              CommandIDs::goToCounterpart,
                              CommandIDs::deleteSelectedItem};

    commands.addArray (ids, numElementsInArray (ids));
}

void ProjectContentComponent::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    String documentName;
    if (currentDocument != nullptr)
        documentName = " '" + currentDocument->getName().substring (0, 32) + "'";

   #if JUCE_MAC
    const ModifierKeys cmdCtrl (ModifierKeys::ctrlModifier | ModifierKeys::commandModifier);
   #else
    const ModifierKeys cmdCtrl (ModifierKeys::ctrlModifier | ModifierKeys::altModifier);
   #endif

    switch (commandID)
    {
    case CommandIDs::saveProject:
        result.setInfo ("Save Project",
                        "Saves the current project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        break;

    case CommandIDs::closeProject:
        result.setInfo ("Close Project",
                        "Closes the current project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        break;

    case CommandIDs::saveDocument:
        result.setInfo ("Save" + documentName,
                        "Saves the current document",
                        CommandCategories::general, 0);
        result.setActive (currentDocument != nullptr || project != nullptr);
        result.defaultKeypresses.add (KeyPress ('s', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::saveDocumentAs:
        result.setInfo ("Save As...",
                        "Saves the current document to a new location",
                        CommandCategories::general, 0);
        result.setActive (currentDocument != nullptr);
        result.defaultKeypresses.add (KeyPress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
        break;

    case CommandIDs::closeDocument:
        result.setInfo ("Close" + documentName,
                        "Closes the current document",
                        CommandCategories::general, 0);
        result.setActive (contentView != nullptr);
        result.defaultKeypresses.add (KeyPress ('w', cmdCtrl, 0));
        break;

    case CommandIDs::goToPreviousDoc:
        result.setInfo ("Previous Document", "Go to previous document", CommandCategories::general, 0);
        result.setActive (recentDocumentList.canGoToPrevious());
        result.defaultKeypresses.add (KeyPress (KeyPress::leftKey, cmdCtrl, 0));
        break;

    case CommandIDs::goToNextDoc:
        result.setInfo ("Next Document", "Go to next document", CommandCategories::general, 0);
        result.setActive (recentDocumentList.canGoToNext());
        result.defaultKeypresses.add (KeyPress (KeyPress::rightKey, cmdCtrl, 0));
        break;

    case CommandIDs::goToCounterpart:
        result.setInfo ("Open corresponding header or cpp file", "Open counterpart file", CommandCategories::general, 0);
        result.setActive (canGoToCounterpart());
        result.defaultKeypresses.add (KeyPress (KeyPress::upKey, cmdCtrl, 0));
        break;

    case CommandIDs::showFilePanel:
        result.setInfo ("Show File Panel",
                        "Shows the tree of files for this project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        result.defaultKeypresses.add (KeyPress ('p', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::showConfigPanel:
        result.setInfo ("Show Config Panel",
                        "Shows the build options for the project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        result.defaultKeypresses.add (KeyPress ('i', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::showProjectSettings:
        result.setInfo ("Show Project Settings",
                        "Shows the main project options page",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        result.defaultKeypresses.add (KeyPress ('i', ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
        break;

    case CommandIDs::deleteSelectedItem:
        result.setInfo ("Delete Selected File", String(), CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress (KeyPress::deleteKey, 0, 0));
        result.defaultKeypresses.add (KeyPress (KeyPress::backspaceKey, 0, 0));
        result.setActive (dynamic_cast<TreePanelBase*> (treeViewTabs.getCurrentContentComponent()) != nullptr);
        break;

    default:
        break;
    }
}

bool ProjectContentComponent::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::saveProject:
        case CommandIDs::closeProject:
        case CommandIDs::saveDocument:
        case CommandIDs::saveDocumentAs:
        case CommandIDs::closeDocument:
        case CommandIDs::goToPreviousDoc:
        case CommandIDs::goToNextDoc:
        case CommandIDs::goToCounterpart:
            if (reinvokeCommandAfterCancellingModalComps (info))
            {
                grabKeyboardFocus(); // to force any open labels to close their text editors
                return true;
            }

            break;

        default:
            break;
    }

    if (isCurrentlyBlockedByAnotherModalComponent())
        return false;

    switch (info.commandID)
    {
        case CommandIDs::saveProject:               saveProject(); break;
        case CommandIDs::closeProject:              closeProject(); break;
        case CommandIDs::saveDocument:              saveDocument(); break;
        case CommandIDs::saveDocumentAs:            saveAs(); break;

        case CommandIDs::closeDocument:             closeDocument(); break;
        case CommandIDs::goToPreviousDoc:           goToPreviousFile(); break;
        case CommandIDs::goToNextDoc:               goToNextFile(); break;
        case CommandIDs::goToCounterpart:           goToCounterpart(); break;

        case CommandIDs::showFilePanel:             showFilesTab(); break;
        case CommandIDs::showConfigPanel:           showConfigTab(); break;
        case CommandIDs::showProjectSettings:       showProjectSettings(); break;

        case CommandIDs::deleteSelectedItem:        deleteSelectedTreeItems(); break;

        default:
            return false;
    }

    return true;
}

void ProjectContentComponent::getSelectedProjectItemsBeingDragged (const DragAndDropTarget::SourceDetails& dragSourceDetails,
                                                                   OwnedArray<Project::Item>& selectedNodes)
{
    FileTreeItemTypes::ProjectTreeItemBase::getSelectedProjectItemsBeingDragged (dragSourceDetails, selectedNodes);
}

//==============================================================================


void ProjectContentComponent::timerCallback()
{
    
}

void ProjectContentComponent::handleMissingSystemHeaders()
{
   #if JUCE_MAC
    const String alertWindowMessage = "Missing system headers\nPlease install a recent version of Xcode";
   #elif JUCE_WINDOWS
    const String alertWindowMessage = "Missing system headers\nPlease install a recent version of Visual Studio and the Windows Desktop SDK";
   #elif JUCE_LINUX
    const String alertWindowMessage = "Missing system headers\nPlease do sudo apt-get install ...";
   #endif

    deleteProjectTabs();
    createProjectTabs();

    AlertWindow::showMessageBox (AlertWindow::AlertIconType::WarningIcon,
                                 "Missing system headers", alertWindowMessage);
}
