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

#ifndef JUCER_NEWPROJECTWIZARDCOMPONENT_H_INCLUDED
#define JUCER_NEWPROJECTWIZARDCOMPONENT_H_INCLUDED

//==============================================================================
/**
    The Component for project creation.
    Features a file browser to select project destination and
    a list box of platform targets to generate.
*/
class WizardComp  : public Component,
                    private ButtonListener,
                    private ComboBoxListener,
                    private TextEditorListener,
                    private FileBrowserListener
{
public:
    WizardComp()
        : projectName (TRANS("Project name")),
          nameLabel (String(), TRANS("Project Name") + ":"),
          typeLabel (String(), TRANS("Project Type") + ":"),
          fileBrowser (FileBrowserComponent::saveMode
                         | FileBrowserComponent::canSelectDirectories
                         | FileBrowserComponent::doNotClearFileNameOnRootChange,
                       NewProjectWizardClasses::getLastWizardFolder(), nullptr, nullptr),
          fileOutline (String(), TRANS("Project Folder") + ":"),
          createButton (TRANS("Create") + "..."),
          cancelButton (TRANS("Cancel"))
    {
        setOpaque (false);

        addChildAndSetID (&projectName, "projectName");
        projectName.setText ("NewProject");
        projectName.setBounds ("120, 34, parent.width / 2 - 10, top + 22");
        nameLabel.attachToComponent (&projectName, true);
        projectName.addListener (this);

        addChildAndSetID (&projectType, "projectType");
        projectType.addItemList (getWizardNames(), 1);
        projectType.setSelectedId (1, dontSendNotification);
        projectType.setBounds ("120, projectName.bottom + 4, projectName.right, top + 22");
        typeLabel.attachToComponent (&projectType, true);
        projectType.addListener (this);

        addChildAndSetID (&fileOutline, "fileOutline");
        fileOutline.setColour (GroupComponent::outlineColourId, Colours::black.withAlpha (0.2f));
        fileOutline.setTextLabelPosition (Justification::centred);
        fileOutline.setBounds ("30, projectType.bottom + 20, projectType.right, parent.height - 30");

        addChildAndSetID (&targetsOutline, "targetsOutline");
        targetsOutline.setColour (GroupComponent::outlineColourId, Colours::black.withAlpha (0.2f));
        targetsOutline.setTextLabelPosition (Justification::centred);
        targetsOutline.setBounds ("fileOutline.right + 20, projectType.bottom + 20, parent.width - 30, parent.height - 70");

        addChildAndSetID (&fileBrowser, "fileBrowser");
        fileBrowser.setBounds ("fileOutline.left + 10, fileOutline.top + 20, fileOutline.right - 10, fileOutline.bottom - 32");
        fileBrowser.setFilenameBoxLabel ("Folder:");
        fileBrowser.setFileName (File::createLegalFileName (projectName.getText()));
        fileBrowser.addListener (this);

        addChildAndSetID (&createButton, "createButton");
        createButton.setBounds ("right - 130, bottom - 34, parent.width - 30, parent.height - 30");
        createButton.addListener (this);

        addChildAndSetID (&cancelButton, "cancelButton");
        cancelButton.addShortcut (KeyPress (KeyPress::escapeKey));
        cancelButton.setBounds ("right - 130, createButton.top, createButton.left - 10, createButton.bottom");
        cancelButton.addListener (this);

        updateCustomItems();
        updateCreateButton();
    }

    void paint (Graphics& g) override
    {
        Rectangle<int> rect = getLocalBounds().reduced (10, 10);

        g.setColour (Colours::white.withAlpha (0.3f));
        g.fillRect (rect);
        g.fillRect (rect.reduced (10, 10));
    }

    void buttonClicked (Button* b) override
    {
        if (b == &createButton)
        {
            createProject();
        }
        else if (b == &cancelButton)
        {
            returnToTemplatesPage();
        }
    }

    void returnToTemplatesPage()
    {
        if (SlidingPanelComponent* parent = findParentComponentOfClass<SlidingPanelComponent>())
        {
            if (parent->getNumTabs() > 0)
                parent->goToTab (parent->getCurrentTabIndex() - 1);
        }
        else
        {
            jassertfalse;
        }
    }

    void createProject()
    {
        MainWindow* mw = Component::findParentComponentOfClass<MainWindow>();
        jassert (mw != nullptr);

        ScopedPointer<NewProjectWizardClasses::NewProjectWizard> wizard (createWizard());

        if (wizard != nullptr)
        {
            Result result (wizard->processResultsFromSetupItems (*this));

            if (result.failed())
            {
                AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                             TRANS("Create Project"),
                                             result.getErrorMessage());
                return;
            }

            ScopedPointer<Project> project (wizard->runWizard (*this, projectName.getText(),
                                                               fileBrowser.getSelectedFile (0)));

            if (project != nullptr)
                mw->setProject (project.release());
        }
    }

    void updateCustomItems()
    {
        customItems.clear();

        ScopedPointer<NewProjectWizardClasses::NewProjectWizard> wizard (createWizard());

        if (wizard != nullptr)
            wizard->addSetupItems (*this, customItems);
    }

    void comboBoxChanged (ComboBox*) override
    {
        updateCustomItems();
    }

    void textEditorTextChanged (TextEditor&) override
    {
        updateCreateButton();
        fileBrowser.setFileName (File::createLegalFileName (projectName.getText()));
    }

    void selectionChanged() override {}

    void fileClicked (const File&, const MouseEvent&) override {}
    void fileDoubleClicked (const File&) override {}

    void browserRootChanged (const File&) override
    {
        fileBrowser.setFileName (File::createLegalFileName (projectName.getText()));
    }

    ComboBox projectType;

private:
    TextEditor projectName;
    Label nameLabel, typeLabel;
    FileBrowserComponent fileBrowser;
    GroupComponent fileOutline;
    GroupComponent targetsOutline;
    TextButton createButton, cancelButton;
    OwnedArray<Component> customItems;

    NewProjectWizardClasses::NewProjectWizard* createWizard()
    {
        return createWizardType (projectType.getSelectedItemIndex());
    }

    void updateCreateButton()
    {
        createButton.setEnabled (projectName.getText().trim().isNotEmpty());
    }
};


#endif   // JUCER_NEWPROJECTWIZARDCOMPONENT_H_INCLUDED
