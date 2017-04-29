#pragma once
#include "../jucer_Headers.h"
#include "skoar.hpp"
#include "noad.hpp"
#include "styles.hpp"
#include "spells.hpp"
#include "skoarpion.hpp"
#include "../Code Editor/SkoarCodeTokeniser.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"

class NoaditesRootItem : public TreeViewItem
{
public:
   
    NoaditesRootItem (const VectorOfNoadites & v, const SkoarStyles::EStyle defaultStyle, const SkoarCodeEditorComponent::ColourScheme & cs);
    ~NoaditesRootItem ();

    bool canBeSelected () const override { return false; }
    bool mightContainSubItems () override { return true; }
    void itemOpennessChanged (bool isNowOpen) override;

private:
    const VectorOfNoadites& noadites;
    const SkoarStyles::EStyle default_style;
    const SkoarCodeEditorComponent::ColourScheme& colour_scheme;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoaditesRootItem)
};


class NoaditesTreeItem : public TreeViewItem
{
public:
    const SkoarStyles::EStyle style;
    const SkoarCodeEditorComponent::ColourScheme& colour_scheme;

    NoaditesTreeItem (const SkoarNoadite& p, const SkoarStyles::EStyle defaultStyle, const SkoarCodeEditorComponent::ColourScheme&);

    bool canBeSelected () const override { return true; }
    bool mightContainSubItems () override { return false; }

    void paintItem (Graphics&, int, int) override;
    void itemSelectionChanged (bool isNowSelected) override;
    bool isNoadite (const SkoarNoadite&);

private:
    const SkoarNoadite& noadite;
    Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoaditesTreeItem)
};

class NoaditesListComponent : public Component
{
public:
    NoaditesListComponent (SkoarpionProjectionPtr);
    ~NoaditesListComponent ();

    void paint (Graphics&) override;
    void resized () override;
    void selectNoadite (const SkoarNoadite&);

private:

    class : public LookAndFeel_V3
    {
    public:
        int getTreeViewIndentSize (TreeView&) override {
            return 8;
        }
    } LNF;

    SkoarNoadPtr rootNoad;
    TreeView tree;
    ScopedPointer<NoaditesRootItem> rootItem;
    SkoarpionProjectionPtr projection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoaditesListComponent)
};
