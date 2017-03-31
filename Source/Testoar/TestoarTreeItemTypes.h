#pragma once
#include "../jucer_Headers.h"
#include "../Utility/jucer_JucerTreeViewBase.h"
#include "../Application/jucer_MainWindow.h"
#include "../Application/jucer_Application.h"
#include "testoar.hpp"
#include "Testoar.h"

struct TestoarTreeItemTypes
{

    //==============================================================================
    class RolloverHelpComp : public Component,
        private Timer
    {
    public:
        RolloverHelpComp() : lastComp(nullptr)
        {
            setInterceptsMouseClicks(false, false);
            startTimer(150);
        }

        void paint(Graphics& g) override
        {
            AttributedString s;
            s.setJustification(Justification::centredLeft);
            s.append(lastTip, Font(14.0f), findColour(mainBackgroundColourId).contrasting(0.7f));

            TextLayout tl;
            tl.createLayoutWithBalancedLineLengths(s, getWidth() - 10.0f);
            if (tl.getNumLines() > 3)
                tl.createLayout(s, getWidth() - 10.0f);

            tl.draw(g, getLocalBounds().toFloat());
        }

    private:
        Component* lastComp;
        String lastTip;

        void timerCallback() override
        {
            Component* newComp = Desktop::getInstance().getMainMouseSource().getComponentUnderMouse();

            if (newComp != nullptr
                && (newComp->getTopLevelComponent() != getTopLevelComponent()
                    || newComp->isCurrentlyBlockedByAnotherModalComponent()))
                newComp = nullptr;

            if (newComp != lastComp)
            {
                lastComp = newComp;

                String newTip(findTip(newComp));

                if (newTip != lastTip)
                {
                    lastTip = newTip;
                    repaint();
                }
            }
        }

        static String findTip(Component* c)
        {
            while (c != nullptr)
            {
                if (TooltipClient* tc = dynamic_cast<TooltipClient*> (c))
                {
                    const String tip(tc->getTooltip());

                    if (tip.isNotEmpty())
                        return tip;
                }

                c = c->getParentComponent();
            }

            return String();
        }
    };


    //==============================================================================
    class TestoarTreeItemBase : public JucerTreeViewBase
    {
    public:

        TestoarTreeItemBase() : testState(Testoar::unknown) {}
        
        Icon getIcon() const override {
            Colour colour;

            if (testState == Testoar::passed)
                return Icon(getIcons().box, Colours::green);

            if (testState == Testoar::failed)
                return Icon(getIcons().warning, Colours::darkred);

            return Icon(getIcons().box, Colours::deepskyblue);
        }

        void showResultsComponent(String &title)
        {
            if (ProjectContentComponent* pcc = getProjectContentComponent()) {
                pcc->setEditorComponent(resultsUi = new TestoarResultsComponent(), nullptr);
                resultsUi->setTitle(title);
            }
        }

        /*void closeSettingsPage()
        {
            if (ProjectContentComponent* pcc = getProjectContentComponent())
            {
                if (TestoarResultsComponent* ppv = dynamic_cast<TestoarResultsComponent*> (pcc->getEditorComponent()))
                    if (ppv->viewport.getViewedComponent()->getComponentID() == getUniqueName())
                        pcc->hideEditor();
            }
        }*/

        void itemOpennessChanged(bool isNowOpen) override
        {
            if (isNowOpen)
                refreshSubItems();
        }

        virtual bool isProjectSettings() const { return false; }

        void refreshAllItems() {
            static_cast<JucerTreeViewBase*>(getOwnerView()->getRootItem())->refreshSubItems();
        }

    protected:
        TestoarResultsComponent* resultsUi;
        Testoar::ETestState testState;
    private:
        //==============================================================================
        
    };

    //==============================================================================
    class RootItem : public TestoarTreeItemBase
    {
    public:
        RootItem()
        {
            testState = Testoar::ETestState::unknown;
        }

        bool isRoot() const override { return true; }
        bool isProjectSettings() const override { return false; }
        String getRenamingName() const override { return getDisplayName(); }
        String getDisplayName() const override { return String("root"); }
        void setName(const String&) override {}
        bool isMissing() override { return false; }
        
        void showDocument() override {}
        bool canBeSelected() const override { return true; }
        String getUniqueName() const override { return "testoar_root"; }
        bool mightContainSubItems() override { return true; }
        void addSubItems() override {
            addSubItem(new AllTestsItem());
        }
        void showPopupMenu() override {}

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RootItem)
    };

    class AllTestsItem : public TestoarTreeItemBase
    {
    public:
        AllTestsItem()
        {
            testState = Testoar::getStateOfAllTests();
        }

        bool isRoot() const override { return true; }
        bool isProjectSettings() const override { return false; }
        String getRenamingName() const override { return getDisplayName(); }
        String getDisplayName() const override { return String("all tests"); }
        void setName(const String&) override {}
        bool isMissing() override { return false; }

        void showDocument() override {
            auto s = getDisplayName();
            showResultsComponent(s);
            Testoar::runAllTests();
            refreshAllItems();
        }
        bool canBeSelected() const override { return true; }
        String getUniqueName() const override { return "testoar_all_tests"; }
        bool mightContainSubItems() override { return true; }
        void addSubItems() override {
            auto x = TestoarGetListOfTags();
            for (auto tag : x) {
                addSubItem(new TestTagItem(tag));
            }
        }
        void showPopupMenu() override {}

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AllTestsItem)
    };


    class TestTagItem : public TestoarTreeItemBase
    {
    public:
        TestTagItem(String s) :
            tag(s)
        {
            testState = Testoar::getStateOfTag(s.toStdString());
        }

        bool isRoot() const override { return false; }
        bool isProjectSettings() const override { return false; }
        String getRenamingName() const override { return tag; }
        String getDisplayName() const override { return tag; }
        void setName(const String&) override {}
        bool isMissing() override { return false; }
       
        void showDocument() override { 
            showResultsComponent(tag); 
            Testoar::runTag(tag.toStdString());
            refreshAllItems();
        }

        bool canBeSelected() const override { return true; }
        String getUniqueName() const override { return tag; }
        bool mightContainSubItems() override { return true; }
        void addSubItems() override {
            ListOfTestCases x = TestoarGetListOfTestCases(tag.toStdString());
            for (auto testCase : x) {
                addSubItem(new TestCaseItem(testCase));
            }
        }
        void showPopupMenu() override {}

    private:
        String tag;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestTagItem)
    };

    class TestCaseItem : public TestoarTreeItemBase
    {
    public:
        TestCaseItem(String s) :
            name(s)
        {
            testState = Testoar::getStateOfTestCase(s.toStdString());
        }

        bool isRoot() const override { return false; }
        bool isProjectSettings() const override { return false; }
        String getRenamingName() const override { return name; }
        String getDisplayName() const override { return name; }
        void setName(const String&) override {}
        bool isMissing() override { return false; }
        
        void showDocument() override { 
            showResultsComponent(name); 
            std::string s = name.toStdString();

            Testoar::runTestCase(s);
            refreshAllItems();
        }

        bool canBeSelected() const override { return true; }
        String getUniqueName() const override { return name; }
        bool mightContainSubItems() override { return false; }
        void addSubItems() override {
        }
        void showPopupMenu() override {}

    private:
        String name;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestCaseItem)
    };
};
