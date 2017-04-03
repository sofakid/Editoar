#include "../jucer_Headers.h"
#include "SkoarTreeComponent.h"
#include "../Logging/SkoarLogger.hpp"
#include "styles.hpp"
#include "SkoarNoadTableComponent.h"

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
    noad = nullptr;
}

void SkoarNoadTreeItem::paintItem(Graphics& g,
    int width,
    int height
) {
    Rectangle<int> r(0, 0, width, height);
    String str(noad->name.c_str());
    String suf(SkoarStyles::to_int(style));
    String mid(" ");
    String noadstyle(SkoarStyles::to_int(noad->style));


    g.setColour(colour);
    g.drawText(str + mid + suf + mid + noadstyle, r, Justification::left);


}

void SkoarNoadTreeItem::itemClicked(const MouseEvent& e) {
    auto x = new SkoarNoadTableComponent(noad);
    x->setAlwaysOnTop(true);
    auto window = TopLevelWindow::getActiveTopLevelWindow();

    window->addAndMakeVisible(x);

}

// ==== SkoarTreeComponent ==========================================================================
SkoarTreeComponent::SkoarTreeComponent(SkoarNoadPtr pRootNoad) :
    rootNoad(pRootNoad),
    rootItem(nullptr),
    tree(new TreeView())
{
    std::list<SkoarStyles::EStyle> style_stack;
    auto current_style = SkoarStyles::EStyle::skoarpion;
    style_stack.push_back(current_style);

    rootItem = new SkoarNoadTreeItem(rootNoad, current_style);
    
    std::list<SkoarNoadTreeItem*> stack;
    SkoarNoadTreeItem* current = &*rootItem;
    stack.push_back(current);

    addAndMakeVisible(tree);
    tree->setDefaultOpenness(true);
    tree->setRootItem(rootItem);
    
    auto& delThese = deleteTheseLater;

    SkoarNoad::inorderBeforeAfter(rootNoad, [&](SkoarNoadPtr p) {
        auto x = new SkoarNoadTreeItem(p, current_style);
        //delThese.add(x);
        current->addSubItem(x);
        
        stack.push_back(current);
        current = x;

        style_stack.push_back(current_style);
        current_style = x->style;
    },
    [&](SkoarNoadPtr p) {
        stack.pop_back();
        current = stack.back();

        style_stack.pop_back();
        current_style = style_stack.back();

    });
}

SkoarTreeComponent::~SkoarTreeComponent()
{
    rootNoad = nullptr;
}

void SkoarTreeComponent::paint (Graphics&)
{
}

void SkoarTreeComponent::resized()
{
    auto r = getLocalBounds();
    tree->setBounds(r);
}

