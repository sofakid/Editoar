#include "TestoarResultsComponent.h"
#include <regex>
#include "TestoarResultsConsumer.h"

//==============================================================================
TestoarResultsComponent::TestoarResultsComponent ()
{
    addAndMakeVisible (toolbarComponent = new TestoarResultsToolBar());
    addAndMakeVisible (resultsPaneComponent = new TestoarResultsPane());

    setSize (600, 400);

    TestoarResultsConsumer::registerUi(this);
}

TestoarResultsComponent::~TestoarResultsComponent()
{
    TestoarResultsConsumer::unregisterUi(this);

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

void TestoarResultsComponent::setTitle(String& s) {
    toolbarComponent->setText(s);
}

void TestoarResultsComponent::resultsArriving(std::string s) {
    auto str = String(s);
    resultsPaneComponent->insertText(str, Colours::azure);

    std::smatch sm;
    std::regex e("test cases.*(\\d+) passed[ |]*(\\d+)\\s*failed");

    if (std::regex_search(s, sm, e) && sm.size() > 1) {
        auto s_pass = sm.str(1);
        auto s_fail = sm.str(2);

        //auto i_pass = stoi(s_pass);
        auto i_fail = stoi(s_fail);

        if (i_fail == 0) {
            toolbarComponent->testPassed();
        }
        else {
            toolbarComponent->testFailed();
        }
    }
    else {
        std::regex e2("All tests passed");
        if (std::regex_search(s, sm, e2)) {
            toolbarComponent->testPassed();
        }
    }
}

void TestoarResultsComponent::errorsArriving(std::string s) {
    auto str = String(s);
    resultsPaneComponent->insertText(str, Colours::indianred);
}
