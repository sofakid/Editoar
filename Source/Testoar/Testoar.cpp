#include "Testoar.h"
#include <regex>
#include <map>
#include "testoar.hpp"

namespace Testoar {

    CriticalSection objectLock;
    TestoarResultsComponent* ui;

    std::string currentTest;

    std::map<std::string, ETestState> results = {};

}

// --- track results -------------------------------------------------------------
Testoar::ETestState Testoar::getStateOfAllTests() {

    ETestState state = unknown;
    bool all_passed = true;

    ListOfTags tags = TestoarGetListOfTags();
    for (auto tag : tags) {
        state = getStateOfTag(tag);
        if (state == failed) {
            return failed;
        }
        if (state != passed) {
            all_passed = false;
        }
    }

    if (all_passed) {
        return passed;
    }

    return unknown;
}

Testoar::ETestState Testoar::getStateOfTag(std::string tag) {
    ETestState state = results[tag];
    
    if (state != unknown) {
        return state;
    }
    bool all_passed = true;

    ListOfTestCases cases = TestoarGetListOfTestCases(tag);
    for (auto tc : cases) {
        state = results[tc];
        if (state == failed) {
            results[tag] = failed;
            return failed;
        }
        if (state != passed)
            all_passed = false;
    }
    if (all_passed) {
        results[tag] = passed;
        return passed;
    }
    return unknown;
}

Testoar::ETestState Testoar::getStateOfTestCase(std::string name) {
    return results[name];
}

// --- register / unregister ui -------------------------------------------------------
void Testoar::registerUi(TestoarResultsComponent* component) {
    const ScopedLock myScopedLock(objectLock);

    ui = component;
}

void Testoar::unregisterUi(TestoarResultsComponent* component) {
    const ScopedLock myScopedLock(objectLock);

    if (ui == component) {
        ui = nullptr;
    }
}

// --- output hooks ------------------------------------------------------------------
void Testoar::out(std::string s) {
    const ScopedLock myScopedLock(objectLock);

    if (ui != nullptr) {
        ui->resultsArriving(s);

        std::smatch sm;
        std::regex e("test cases.*(\\d+) passed[ |]*(\\d+)\\s*failed");

        if (std::regex_search(s, sm, e)) {
            //auto s_pass = sm.str(1);
            auto s_fail = sm.str(2);

            //auto i_pass = stoi(s_pass);
            auto i_fail = stoi(s_fail);

            if (i_fail != 0) {
                ui->testsFailed();
                results[currentTest] = failed;
            }

            String str("");
            ui->setCounts(str);
        }
        else {
            std::regex e2("All tests passed[^\\n]*");
            if (std::regex_search(s, sm, e2)) {
                ui->testsPassed();
                results[currentTest] = passed;
             
                String str("");
                ui->setCounts(str);
            }
        }
    }
}

void Testoar::err(std::string s) {
    const ScopedLock myScopedLock(objectLock);
    if (ui != nullptr) {
        ui->errorsArriving(s);
    }

}

// --- tracking current test ---------------------------------------------
void Testoar::setCurrentTest(std::string s) {
    const ScopedLock myScopedLock(objectLock);

    currentTest = s;
}

void Testoar::setCurrentTest(String s) {
    setCurrentTest(s.toStdString());
}

// --- runners ---------------------------------------------
//
// we run them individually so we can track the results better.
//
// side effect is every test case must have a tag. 
// but I'd insist on that anyways.
void Testoar::runAllTests() {
    auto listy = TestoarGetListOfTags();
    for (auto tag : listy) {
        runTag(tag);
    }
}

void Testoar::runTag(std::string s) {
    auto listy = TestoarGetListOfTestCases(s);
    for (auto tc : listy) {
        runTestCase(tc);
    }
}

void Testoar::runTestCase(std::string s) {
    currentTest = s;
    TestoarRunTestsByTestCase(s);
}


