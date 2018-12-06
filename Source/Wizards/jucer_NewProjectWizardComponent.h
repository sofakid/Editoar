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
class WizardComp : public Component,
                   private Button::Listener,
                   private TextEditor::Listener,
                   private FileBrowserListener
{
public:
    WizardComp()
        : projectName (TRANS("Project name")),
          nameLabel (String(), TRANS("Project Name") + ":"),
          fileBrowser (FileBrowserComponent::saveMode
                         | FileBrowserComponent::canSelectDirectories
                         | FileBrowserComponent::doNotClearFileNameOnRootChange,
                       NewProjectWizardClasses::getLastWizardFolder(), nullptr, nullptr),
          fileOutline (String(), TRANS("Project Folder") + ":"),
          createButton (TRANS("Create") + "...")
    {
        setOpaque (false);

        addChildAndSetID (&projectName, "projectName");
        projectName.setText ("NewProject");
        nameLabel.attachToComponent (&projectName, true);
        projectName.addListener (this);

        addChildAndSetID (&fileOutline, "fileOutline");
        fileOutline.setColour (GroupComponent::outlineColourId, Colours::black.withAlpha (0.2f));
        fileOutline.setTextLabelPosition (Justification::centred);

        addChildAndSetID (&fileBrowser, "fileBrowser");
        fileBrowser.setFilenameBoxLabel ("Folder:");
        fileBrowser.setFileName (File::createLegalFileName (projectName.getText()));
        fileBrowser.addListener (this);

        addChildAndSetID (&createButton, "createButton");
        createButton.addListener (this);

        updateCreateButton();

        setSize (840, 570);
    }

    void paint (Graphics& g) override
    {
        Rectangle<int> rect = getLocalBounds().reduced (10, 10);

        g.setColour (Colours::white.withAlpha (0.3f));
        g.fillRect (rect);
        g.fillRect (rect.reduced (10, 10));
    }

    void resized () override
    {
        auto bounds = getLocalBounds ().reduced (20, 20);
        Rectangle<int> projectNameBounds (120, 34, bounds.getWidth () / 2 - 10, 25);

        bounds.removeFromTop (projectNameBounds.getBottom ());

        bounds.removeFromBottom (10);
        auto buttons = bounds.removeFromBottom (34);

        bounds.reduce (30, 5);

        auto fileOutlineBounds = bounds;
        auto fileBrowserBounds = fileOutlineBounds.reduced (15, 25);

        buttons.removeFromRight (30);
        auto createButtonBounds = buttons.removeFromRight (100);

        projectName.setBounds (projectNameBounds);
        fileOutline.setBounds (fileOutlineBounds);
        fileBrowser.setBounds (fileBrowserBounds);
        createButton.setBounds (createButtonBounds);
    }

    void buttonClicked (Button* b) override
    {
        if (b == &createButton)
            createProject();
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
    Label nameLabel;
    FileBrowserComponent fileBrowser;
    GroupComponent fileOutline;
    TextButton createButton;

    NewProjectWizardClasses::NewProjectWizard* createWizard()
    {
        //return createWizardType (projectType.getSelectedItemIndex());
        return createWizardType (0);
    }

    void updateCreateButton()
    {
        createButton.setEnabled (projectName.getText().trim().isNotEmpty());
    }
};


#endif   // JUCER_NEWPROJECTWIZARDCOMPONENT_H_INCLUDED
