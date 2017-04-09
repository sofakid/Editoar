#include "../jucer_Headers.h"
#include "SkoarTreeComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "styles.hpp"
#include "SkoarNoadTableComponent.h"

#include "DebuggoarComponent.h"
#include "DebuggoarDeetsPanel.h"

// we need a reference to editor if we want to get the configured colours, todo.
const Colour skoar_colours[41] = {
    Colour(0xffffffff),
    Colour(0xffCC2222),
    Colour(0xffFFF82E),
    Colour(0xffFFF82E),
    Colour(0xffFFF82E),
    Colour(0xff1EFA67),
    Colour(0xffEEEECC),
    Colour(0xffE5E5B5),
    Colour(0xffB340B1),
    Colour(0xffB340B1),
    Colour(0xffFFF82E),
    Colour(0xff9DB562),
    Colour(0xffB340B1),
    Colour(0xffB340B1),
    Colour(0xff0B6BD9),
    Colour(0xffFF99FF),
    Colour(0xffFFF82E),
    Colour(0xffB58962),
    Colour(0xff1EFA67),
    Colour(0xffB340B1),
    Colour(0xffB340B1),
    Colour(0xffFFF82E),
    Colour(0xffFFF82E),
    Colour(0xffEEEECC),
    Colour(0xffF8FF2E),
    Colour(0xffFFF82E),
    Colour(0xff998877),
    Colour(0xff888888),
    Colour(0xffFF2E2E),
    Colour(0xffCCDDFF),
    Colour(0xffB340B1),
    Colour(0xff999999),
    Colour(0xff6699EE),
    Colour(0xff1EB1FA),
    Colour(0xffB59D62),
    Colour(0xff9DB562),
    Colour(0xff77EE77),
    Colour(0xffCCCCCC),
    Colour(0xff62B59D),
    Colour(0xff1EAE1E),
    Colour(0xff333344)
};

// === SkoarNoadTreeItem ===========================================================================
SkoarNoadTreeItem::SkoarNoadTreeItem(SkoarNoadPtr p) :
    noad(p),
    style(p->style),
    colour(skoar_colours[SkoarStyles::to_int(style)])
{
}

SkoarNoadTreeItem::SkoarNoadTreeItem(
    SkoarNoadPtr p,
    const SkoarStyles::EStyle defaultStyle) :
    noad(p),
    style(p->style == SkoarStyles::EStyle::nostyle ? defaultStyle : p->style)
{
    colour = skoar_colours[SkoarStyles::to_int(style)];
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
    if (isNowSelected) {
        auto d = DebuggoarDeets::getInstance();

        d->showNoad(noad);
        d->showSkoarpuscle(noad->skoarpuscle);
    }
}

void SkoarNoadTreeItem::itemOpennessChanged(bool isNowOpen) {

    if (isNowOpen) {
        for (auto x : noad->children) {
            addSubItem(new SkoarNoadTreeItem(x, style));
        }
    } 
    else {
        clearSubItems();
    }
}

bool SkoarNoadTreeItem::isNoad(SkoarNoad* p) {
    return noad.get() == p;
}


// ==== SkoarTreeComponent ==========================================================================
SkoarTreeComponent::SkoarTreeComponent(SkoarNoadPtr pRootNoad) :
    rootNoad(pRootNoad),
    rootItem(nullptr),
    tree()
{
    rootItem = new SkoarNoadTreeItem(rootNoad, SkoarStyles::EStyle::skoarpion);
    
    tree.setLookAndFeel(&LNF);
    tree.setDefaultOpenness(true);
    tree.setRootItem(rootItem);
    addAndMakeVisible(tree);

    setSize(300, 400);

}

SkoarTreeComponent::~SkoarTreeComponent()
{
    rootItem = nullptr;
    rootNoad = nullptr;
}

void SkoarTreeComponent::paint (Graphics&)
{
}

void SkoarTreeComponent::resized()
{
    auto r = getLocalBounds();
    tree.setBounds(r);
}

void SkoarTreeComponent::selectNoad(SkoarNoad* noad) {

    auto rows = tree.getNumRowsInTree();
    for (int i = 0; i < rows; ++i) {
        auto child = static_cast<SkoarNoadTreeItem*>(tree.getItemOnRow(i));
        if (child->isNoad(noad)) {
            child->setSelected(true, true, NotificationType::sendNotification);
            break;
        }
    }

}

