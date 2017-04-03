#include "SkoarProjectionsComponent.h"

#include "../Logging/SkoarLogger.hpp"

#include "skoarpion.hpp"
#include "koar.hpp"

SkoarProjectionsComponent::SkoarProjectionsComponent() :
    tabby(new TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop))
{

    Skoar skoar(L"seven: 7  {? $ == c# ?? =^.^= ?? ^^(;,;)^^ ?} \n  a# ) \n {: )) :: 3 times :}", &SkoarLog);
    addAndMakeVisible(tabby);

    auto colour = Colours::black;
    ListOfSkoarStrings voices = skoar.get_all_voices();

    auto skoarpion = skoar.skoarpions.front();

    auto projections = Skoarpion::get_projections(skoarpion, voices);

    for (auto projection : *projections) {
        tabby->addTab(projection->proj->voice->name.c_str(), colour, 
            new SkoarTreeComponent(projection->proj), true);
    }

}

SkoarProjectionsComponent::~SkoarProjectionsComponent() {

}


void SkoarProjectionsComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}


void SkoarProjectionsComponent::resized()
{
    auto r = getLocalBounds();
    tabby->setBounds(r);
}
