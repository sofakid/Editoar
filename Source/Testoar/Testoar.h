#pragma once
#include "TestoarResultsComponent.h"
#include <list>
typedef std::list<std::string> ListOfSections;

namespace Testoar {
    enum ETestState {
        unknown,
        passed,
        failed
    };

    void initialize();

    void registerUi(TestoarResultsComponent* component);
    void unregisterUi(TestoarResultsComponent* component);

    void out(std::string s);
    void err(std::string s);

    ETestState getStateOfAllTests();
    ETestState getStateOfTag(std::string name);
    ETestState getStateOfTestCase(std::string name);
    ETestState getStateOfTestCaseSection(std::string tc, std::string section);

    ListOfSections getListOfTestCaseSections(std::string tc);

    void setCurrentTest(std::string s);
    void setCurrentTest(String s);

    void setCurrentSection(std::string s);
    void currentTestPassed();
    void currentTestFailed();


    void runAllTests();
    void runTag(std::string s);
    void runTestCase(std::string s);
    void runTestCaseSection(std::string, std::string);

    void updateUiTag(std::string);
    void updateUiTestCase(std::string);
    void updateUiSection(std::string, std::string);

}