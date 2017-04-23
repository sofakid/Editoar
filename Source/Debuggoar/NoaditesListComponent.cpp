#include "../jucer_Headers.h"
#include "NoaditesListComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "styles.hpp"
#include "SkoarNoadTableComponent.h"

#include "DebuggoarComponent.h"
#include "DebuggoarDeetsPanel.h"

// === NoaditesRootItem ===========================================================================
NoaditesRootItem::NoaditesRootItem (
    const VectorOfNoadites& v,
    const SkoarStyles::EStyle defaultStyle,
    const SkoarCodeEditorComponent::ColourScheme& cs) :
    noadites (v),
    colour_scheme (cs),
    default_style (defaultStyle)
{
}

NoaditesRootItem::~NoaditesRootItem ()
{
    clearSubItems ();
}

void NoaditesRootItem::itemOpennessChanged (bool isNowOpen) {

    if (isNowOpen)
    {
        for (const auto& x : noadites)
        {
            addSubItem (new NoaditesTreeItem (x, default_style, colour_scheme));
        }
    }
    else
    {
        clearSubItems ();
    }
}

// === NoaditesTreeItem ===========================================================================
NoaditesTreeItem::NoaditesTreeItem (
    const SkoarNoadite& p,
    const SkoarStyles::EStyle defaultStyle,
    const SkoarCodeEditorComponent::ColourScheme& cs) :
    colour_scheme (cs),
    noadite (p),
    style (p.style == SkoarStyles::EStyle::nostyle ? defaultStyle : p.style)
{
    colour = colour_scheme.types.getUnchecked (SkoarStyles::to_int (style)).colour;
}

void NoaditesTreeItem::paintItem (Graphics& g,
    int width,
    int height
) {
    Rectangle<int> r (0, 0, width, height);
    String str (noadite.name.c_str ());

    g.setColour (colour);
    g.drawText (str, r, Justification::left);
}

void NoaditesTreeItem::itemSelectionChanged (bool isNowSelected) {
    if (isNowSelected)
    {
        auto d = DebuggoarDeets::getInstance ();

        d->showNoadite (noadite);
        d->showSkoarpuscle (noadite.skoarpuscle);

        auto deb = DebuggoarComponent::getDebuggoar ();

        deb->focusOnNoadite (noadite);

    }
}

bool NoaditesTreeItem::isNoadite (SkoarNoadite* p) {
    return noadite.offs == p->offs && noadite.kind == p->kind;
}



// ==== NoaditesListComponent ==========================================================================
NoaditesListComponent::NoaditesListComponent (SkoarpionProjectionPtr p) :
    rootItem (nullptr),
    tree ()
{
    auto cs = DebuggoarComponent::getColourScheme ();
    rootItem = new NoaditesRootItem (p->noadites, SkoarStyles::EStyle::skoarpion, cs);

    tree.setLookAndFeel (&LNF);
    tree.setDefaultOpenness (true);
    tree.setRootItem (rootItem);
    tree.setRootItemVisible (false);
    tree.setColour (TreeView::ColourIds::selectedItemBackgroundColourId, Colours::darkcyan.withAlpha (0.5f));
    addAndMakeVisible (tree);

    setSize (300, 400);
}

NoaditesListComponent::~NoaditesListComponent ()
{
    rootItem = nullptr;
    rootNoad = nullptr;
}

void NoaditesListComponent::paint (Graphics&)
{
}

void NoaditesListComponent::resized ()
{
    auto r = getLocalBounds ();
    tree.setBounds (r);
}

#define NAICE 5
void NoaditesListComponent::selectNoad (SkoarNoadite* noadite) {

    auto rows = tree.getNumRowsInTree ();
    for (int i = 0; i < rows; ++i)
    {
        auto child = static_cast<NoaditesTreeItem*>(tree.getItemOnRow (i));
        if (child->isNoadite (noadite))
        {
            child->setSelected (true, true, NotificationType::sendNotification);

            if (rows - i < NAICE)
            {
                auto scrollTo = static_cast<NoaditesTreeItem*>(tree.getItemOnRow (rows - 1));
                tree.scrollToKeepItemVisible (scrollTo);
                tree.scrollToKeepItemVisible (child);

            }
            else
            {
                auto scrollTo = static_cast<NoaditesTreeItem*>(tree.getItemOnRow (i + NAICE));
                tree.scrollToKeepItemVisible (scrollTo);
                tree.scrollToKeepItemVisible (child);
            }
            break;
        }
    }

}

