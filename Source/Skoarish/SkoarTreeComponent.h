#pragma once
#include "../jucer_Headers.h"
#include "skoar_public.hpp"
#include "../Code Editor/SkoarCodeTokeniser.hpp"
#include "../Code Editor/SkoarCodeEditor.hpp"

class SkoarNoadTreeItem : public TreeViewItem {
public:
    const SkoarStyles::EStyle style;

    SkoarNoadTreeItem(SkoarNoadPtr p);
    SkoarNoadTreeItem(SkoarNoadPtr p, const SkoarStyles::EStyle defaultStyle);
    ~SkoarNoadTreeItem();

    bool canBeSelected() const override { return true; }
    bool mightContainSubItems() override { return true; }

    void paintItem(Graphics&, int, int) override;

    /** Called when the user clicks on this item.

    If you're using createItemComponent() to create a custom component for the
    item, the mouse-clicks might not make it through to the treeview, but this
    is how you find out about clicks when just drawing each item individually.

    The associated mouse-event details are passed in, so you can find out about
    which button, where it was, etc.

    @see itemDoubleClicked
    */
    void itemClicked(const MouseEvent& e) override;

private:
    SkoarNoadPtr noad;
    Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkoarNoadTreeItem)
};

class SkoarTreeComponent : public Component
{
public:
    SkoarTreeComponent(SkoarNoadPtr);
    ~SkoarTreeComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    SkoarNoadPtr rootNoad;
    ScopedPointer<TreeView> tree;
    ScopedPointer<SkoarNoadTreeItem> rootItem;

    OwnedArray<SkoarNoadTreeItem> deleteTheseLater;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkoarTreeComponent)
};
