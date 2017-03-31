#pragma once
#include "TestoarResultsComponent.h"

namespace Testoar {
    enum ETestState {
        unknown,
        passed,
        failed
    };

    void registerUi(TestoarResultsComponent* component);
    void unregisterUi(TestoarResultsComponent* component);

    void out(std::string s);
    void err(std::string s);

    ETestState getStateOfAllTests();
    ETestState getStateOfTag(std::string name);
    ETestState getStateOfTestCase(std::string name);

    void setCurrentTest(std::string s);
    void setCurrentTest(String s);

    void runAllTests();
    void runTag(std::string s);
    void runTestCase(std::string s);

}