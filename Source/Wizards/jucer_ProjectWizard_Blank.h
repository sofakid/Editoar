
struct BlankAppWizard   : public NewProjectWizard
{
    BlankAppWizard()  {}

    String getName() const override         { return TRANS("Empty Application"); }
    String getDescription() const override  { return TRANS("Creates a blank Skoarbook."); }
    const char* getIcon() const override    { return BinaryData::wizard_Openfile_svg; }

    bool initialiseProject (Project& project) override
    {
        createSourceFolder();
        project.getProjectTypeValue() = ProjectType_GUIApp::getTypeName();
        Project::Item sourceGroup (createSourceGroup (project));
        
        return true;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlankAppWizard)
};
