#pragma once

#include "TestoarResultsToolBar.h"
#include "TestoarResultsPane.h"

//==============================================================================
class TestoarResultsComponent  : public Component
{
public:
    //==============================================================================
    TestoarResultsComponent();
    ~TestoarResultsComponent();

    void paint (Graphics& g) override;
    void resized() override;

    void testsPassed();
    void testsFailed();

    void setTitle(String& s);
    void setCounts(String &counts);

    void resultsArriving(std::string s);
    void errorsArriving(std::string s);

    String getResultsText ();

private:
    //==============================================================================
    ScopedPointer<TestoarResultsToolBar> toolbarComponent;
    ScopedPointer<TestoarResultsPane> resultsPaneComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestoarResultsComponent)
};
