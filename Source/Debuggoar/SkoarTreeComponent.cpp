#include "../jucer_Headers.h"
#include "SkoarTreeComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "styles.hpp"
#include "SkoarNoadTableComponent.h"

#include "DebuggoarComponent.h"
#include "DebuggoarDeetsPanel.h"

// === SkoarNoadTreeItem ===========================================================================
SkoarNoadTreeItem::SkoarNoadTreeItem(
    SkoarNoadPtr p,
    const SkoarStyles::EStyle defaultStyle, 
    const SkoarCodeEditorComponent::ColourScheme& cs) :
    colour_scheme(cs),
    noad(p),
    style(p == nullptr ? defaultStyle : p->style == SkoarStyles::EStyle::nostyle ? defaultStyle : p->style)
{
    colour = colour_scheme.types.getUnchecked(SkoarStyles::to_int(style)).colour;
}

SkoarNoadTreeItem::~SkoarNoadTreeItem()
{
    clearSubItems();
    noad = nullptr;
}

void SkoarNoadTreeItem::paintItem(Graphics& g,
    int width,
    int height
) {
    if (noad == nullptr)
        return;

    Rectangle<int> r(0, 0, width, height);
    String str(noad->name.c_str());

    g.setColour(colour);
    g.drawText(str, r, Justification::left);
}

void SkoarNoadTreeItem::itemClicked(const MouseEvent&) {
    /*auto d = DebuggoarComponent::getDebuggoar();

    auto rUs = getItemPosition(true);
    Point<int> p(rUs.getRight() + 11, rUs.getY() + 92);

    d->popupNoad(noad, p);*/
}

void SkoarNoadTreeItem::itemSelectionChanged(bool isNowSelected) {
    if (noad == nullptr)
        return;

    if (isNowSelected) {
        auto d = DebuggoarDeets::getInstance();

        d->showNoad(noad);
        d->showSkoarpuscle(noad->skoarpuscle);

        auto deb = DebuggoarComponent::getDebuggoar();

        deb->focusOnNoad(noad);

    }
}

void SkoarNoadTreeItem::itemOpennessChanged(bool isNowOpen) {
    if (noad == nullptr)
        return;

    if (isNowOpen) {
        for (auto x : noad->children) {
            addSubItem(new SkoarNoadTreeItem(x, style, colour_scheme));
        }
    } 
    else {
        clearSubItems();
    }
}

bool SkoarNoadTreeItem::isNoad(SkoarNoad* p) {
    if (noad == nullptr)
        return false;

    return noad.get() == p;
}


// ==== SkoarTreeComponent ==========================================================================
SkoarTreeComponent::SkoarTreeComponent(SkoarNoadPtr pRootNoad) :
    rootNoad(pRootNoad),
    rootItem(nullptr),
    tree()
{
    auto cs = DebuggoarComponent::getColourScheme ();
    rootItem = new SkoarNoadTreeItem(rootNoad, SkoarStyles::EStyle::skoarpion, cs);
    
    tree.setLookAndFeel(&LNF);
    tree.setDefaultOpenness(true);
    tree.setRootItem(rootItem);
    tree.setColour(TreeView::ColourIds::selectedItemBackgroundColourId, Colours::darkcyan.withAlpha(0.5f));
    addAndMakeVisible(tree);

    setSize(300, 400);

}

SkoarTreeComponent::~SkoarTreeComponent()
{
}

void SkoarTreeComponent::paint (Graphics&)
{
}

void SkoarTreeComponent::resized()
{
    auto r = getLocalBounds();
    tree.setBounds(r);
}

#define NAICE 5
void SkoarTreeComponent::selectNoad(SkoarNoad* noad) {

    auto rows = tree.getNumRowsInTree();
    for (int i = 0; i < rows; ++i) {
        auto child = static_cast<SkoarNoadTreeItem*>(tree.getItemOnRow(i));
        if (child->isNoad(noad)) {
            child->setSelected(true, true, NotificationType::sendNotification);
             
            if (rows - i < NAICE) {
                auto scrollTo = static_cast<SkoarNoadTreeItem*>(tree.getItemOnRow(rows-1));
                tree.scrollToKeepItemVisible(scrollTo);
                tree.scrollToKeepItemVisible(child);

            }
            else {
                auto scrollTo = static_cast<SkoarNoadTreeItem*>(tree.getItemOnRow(i + NAICE));
                tree.scrollToKeepItemVisible(scrollTo);
                tree.scrollToKeepItemVisible(child);
            }
            break;
        }
    }

}

