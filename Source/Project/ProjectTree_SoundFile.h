#pragma once

class SoundFileItem   : public SourceFileItem
{
public:
    SoundFileItem (const Project::Item& projectItem)
        : SourceFileItem(projectItem)
    {
        auto mgr = SkoarishInstrumentManager::getInstance();
        auto f = getFile();
        instrument = mgr->getOrCreateInstrumentByFile(f);
        // todo: register this to update when renamed
        auto that = this;
        instrument->setRenameSpell([=](SkoarishInstrument*) {
            that->repaintItem();
        });
        
    }

    bool acceptsFileDrop (const StringArray&) const override             { return false; }
    bool acceptsDragItems (const OwnedArray <Project::Item>&) override   { return false; }

    String getDisplayName() const override
    {
        return instrument->getId();
    }

    void setName (const String& newName) override
    {
        if (newName != File::createLegalFileName (newName))
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon, "File Rename",
                                         "That filename contained some illegal characters!");
            triggerAsyncRename (item);
            return;
        }

        File oldFile (getFile());
        File newFile (oldFile.getSiblingFile (newName));
        
        if (! item.renameFile (newFile))
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon, "File Rename",
                                         "Failed to rename the file!\n\nCheck your file permissions!");
        } 
        else
        {
            instrument->renameFile(newFile);
        }
    }

    ProjectTreeItemBase* createSubItem (const Project::Item&) override
    {
        jassertfalse;
        return nullptr;
    }

    void showDocument() override
    {
        const File f (getFile());

        if (f.exists())
            if (ProjectContentComponent* pcc = getProjectContentComponent())
                pcc->showEditorForFile (f, false);
    }

    void showPopupMenu() override
    {
        PopupMenu m;

        if (GroupItem* parentGroup = dynamic_cast<GroupItem*> (getParentProjectItem()))
        {
            parentGroup->addCreateFileMenuItems (m);
            m.addSeparator();
        }

        m.addItem (1, "Open in external editor");
        m.addItem (2,
                     #if JUCE_MAC
                      "Reveal in Finder");
                     #else
                      "Reveal in Explorer");
                     #endif

        m.addItem (4, "Rename File...");
        m.addSeparator();
        m.addItem (3, "Delete");

        launchPopupMenu (m);
    }

    void handlePopupMenuResult (int resultCode) override
    {
        switch (resultCode)
        {
            case 1:     getFile().startAsProcess(); break; // todo use configured editor (audacity, etc..)
            case 2:     revealInFinder(); break;
            case 3:     deleteAllSelectedItems(); break;
            case 4:     triggerAsyncRename (item); break;

            default:
                if (GroupItem* parentGroup = dynamic_cast<GroupItem*> (getParentProjectItem()))
                    parentGroup->processCreateFileMenuItem (resultCode);

                break;
        }
    }

private:
    SkoarishInstrument *instrument;
};
