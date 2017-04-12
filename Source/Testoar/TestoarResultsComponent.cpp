#include "TestoarResultsComponent.h"
#include <regex>
#include "Testoar.h"

//==============================================================================
TestoarResultsComponent::TestoarResultsComponent ()
{
    addAndMakeVisible (toolbarComponent = new TestoarResultsToolBar());
    addAndMakeVisible (resultsPaneComponent = new TestoarResultsPane());

    setSize (600, 400);

    Testoar::registerUi(this);
}

TestoarResultsComponent::~TestoarResultsComponent()
{
    Testoar::unregisterUi(this);

    toolbarComponent = nullptr;
    resultsPaneComponent = nullptr;
}

//==============================================================================
void TestoarResultsComponent::paint (Graphics&)
{
}

void TestoarResultsComponent::resized()
{
    auto r = getLocalBounds();
    toolbarComponent->setBounds (r.removeFromTop(32));
    resultsPaneComponent->setBounds (r);
}

//==============================================================================
void TestoarResultsComponent::testsPassed() {
    toolbarComponent->testsPassed();
}

void TestoarResultsComponent::testsFailed() {
    toolbarComponent->testsFailed();
}

void TestoarResultsComponent::setCounts(String &counts) {
    toolbarComponent->setCounts(counts);
}

void TestoarResultsComponent::setTitle(String& s) {
    toolbarComponent->setTitle(s);
}

void TestoarResultsComponent::resultsArriving(std::string s) {
    auto str = String(s);
    resultsPaneComponent->insertText(str, Colours::azure);
}

void TestoarResultsComponent::errorsArriving(std::string s) {
    auto str = String(s);
    Colour red(255, 95, 70);
    resultsPaneComponent->insertText(str, red);
}

String TestoarResultsComponent::getResultsText ()
{
    return resultsPaneComponent->getResultsText();
}
