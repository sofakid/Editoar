#include "Testoar.h"
#include <regex>
#include <map>
#include "testoar.hpp"

namespace Testoar
{
    CriticalSection objectLock;
    TestoarResultsComponent* ui;

    std::string currentTestCase ("");
    std::string currentSection ("");

    std::map<std::string, ETestState> results = {};
    std::map<std::string, std::map<std::string, ETestState>> tcResults = {};
}

void Testoar::initialize () {
    TestoarInitialize ([](std::string s) {
        out (s);
    }, [](std::string s) {
        err (s);
    });
}

// --- track results -------------------------------------------------------------
Testoar::ETestState Testoar::getStateOfAllTests () {

    ETestState state = unknown;
    bool all_passed = true;

    ListOfTags tags = TestoarGetListOfTags ();
    for (auto tag : tags)
    {
        state = getStateOfTag (tag);
     
        if (state == failed)
            return failed;
        
        if (state != passed)
            all_passed = false;
    }

    if (all_passed)
        return passed;

    return unknown;
}

Testoar::ETestState Testoar::getStateOfTag (std::string tag) {
    ETestState state = results[tag];

    if (state != unknown)
        return state;
    
    bool all_passed = true;

    ListOfTestCases cases = TestoarGetListOfTestCases (tag);
    for (auto tc : cases)
    {
        state = getStateOfTestCase (tc);
        if (state == failed)
        {
            results[tag] = failed;
            return failed;
        }
        if (state != passed)
            all_passed = false;
    }
    if (all_passed)
    {
        results[tag] = passed;
        return passed;
    }
    return unknown;
}

Testoar::ETestState Testoar::getStateOfTestCase (std::string name) {
    auto tcstate = results[name];
    if (tcstate != unknown)
        return tcstate;

    auto listOfSections = getListOfTestCaseSections (name);
    if (listOfSections.size () == 0)
        return unknown;

    bool all_passed = true;
    for (auto section : listOfSections)
    {
        auto state = getStateOfTestCaseSection (name, section);
        if (state == failed)
        {
            results[name] = failed;
            return failed;
        }

        if (state != passed)
            all_passed = false;
    }

    if (all_passed)
    {
        results[name] = passed;
        return passed;
    }
    return unknown;
}

Testoar::ETestState Testoar::getStateOfTestCaseSection (std::string tc, std::string section) {
    return tcResults[tc][section];
}

ListOfSections Testoar::getListOfTestCaseSections (std::string tc) {
    ListOfSections out;
    for (auto sec_kv : tcResults[tc])
        out.push_back (sec_kv.first);

    return out;
}


// --- register / unregister ui -------------------------------------------------------
void Testoar::registerUi (TestoarResultsComponent* component) {
    const ScopedLock myScopedLock (objectLock);

    ui = component;
}

void Testoar::unregisterUi (TestoarResultsComponent* component) {
    const ScopedLock myScopedLock (objectLock);

    if (ui == component)
        ui = nullptr;
}

// --- output hooks ------------------------------------------------------------------
void Testoar::out (std::string s) {
    const ScopedLock myScopedLock (objectLock);

    if (ui != nullptr)
    {

        std::smatch sm;

        std::regex eSectionEndingPassed ("TESTOAR SECTION PASSED tc<<([^>]*)>> section<<([^>]*)>>\n");
        std::regex eSectionEndingFailed ("TESTOAR SECTION FAILED tc<<([^>]*)>> section<<([^>]*)>>\n");

        auto flags = std::regex_constants::format_first_only;
        bool something_found;
        do
        {
            something_found = false;
            if (std::regex_search (s, sm, eSectionEndingPassed, flags))
            {
                something_found = true;
                currentTestCase = sm.str (1);
                currentSection = sm.str (2);
                currentTestPassed ();
                s = std::regex_replace (s, eSectionEndingPassed, "", flags);
            }
            else if (std::regex_search (s, sm, eSectionEndingFailed, flags))
            {
                something_found = true;
                currentTestCase = sm.str (1);
                currentSection = sm.str (2);
                currentTestFailed ();
                s = std::regex_replace (s, eSectionEndingFailed, "", flags);
            }

        } while (something_found);
       
        ui->resultsArriving (s);
    }
}

void Testoar::err (std::string s) {
    const ScopedLock myScopedLock (objectLock);
    if (ui != nullptr)
        ui->errorsArriving (s);
}

// --- update ui ---------------------------------------------------------
void Testoar::updateUiTag (std::string tag) {
    const ScopedLock myScopedLock (objectLock);
    if (ui != nullptr)
    {
        auto state = getStateOfTag (tag);
        if (state == passed)
            ui->testsPassed ();
        else if (state == failed)
            ui->testsFailed ();
    }
}

void Testoar::updateUiTestCase (std::string tc) {
    const ScopedLock myScopedLock (objectLock);
    if (ui != nullptr)
    {
        auto state = getStateOfTestCase (tc);
        if (state == passed)
            ui->testsPassed ();
        else if (state == failed)
            ui->testsFailed ();
    }
}

void Testoar::updateUiSection (std::string tc, std::string section) {
    const ScopedLock myScopedLock (objectLock);
    if (ui != nullptr)
    {
        auto state = getStateOfTestCaseSection (tc, section);
        if (state == passed)
            ui->testsPassed ();
        else if (state == failed)
            ui->testsFailed ();
    }
}
// --- tracking current test ---------------------------------------------
void Testoar::setCurrentTest (std::string s) {
    currentTestCase = s;
}

void Testoar::setCurrentTest (String s) {
    setCurrentTest (s.toStdString ());
}

void Testoar::setCurrentSection (std::string section) {
    Testoar::currentSection = section;
}

void Testoar::currentTestPassed () {
    tcResults[currentTestCase][currentSection] = passed;
}

void Testoar::currentTestFailed () {
    tcResults[currentTestCase][currentSection] = failed;
}

// --- runners ---------------------------------------------
//
// we run them individually so we can track the results better.
//
// side effect is every test case must have a tag. 
// but I'd insist on that anyways.
void Testoar::runAllTests () {
    auto listy = TestoarGetListOfTags ();
    for (auto tag : listy)
        runTag (tag);
}

void Testoar::runTag (std::string tag) {
    auto listy = TestoarGetListOfTestCases (tag);
    for (auto tc : listy)
        runTestCase (tc);
    
    updateUiTag (tag);
}

void Testoar::runTestCase (std::string tc) {
    TestoarRunTestsByTestCase (tc);
    updateUiTestCase (tc);
}


void Testoar::runTestCaseSection (std::string tc, std::string section) {
    TestoarRunTestsByTestCaseSection (tc, section);
    updateUiSection (tc, section);
}


