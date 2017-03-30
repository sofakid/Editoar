#include "TestoarResultsConsumer.h"

namespace TestoarResultsConsumer {

    CriticalSection objectLock;
    TestoarResultsComponent* ui;
}

void TestoarResultsConsumer::registerUi(TestoarResultsComponent* component) {
    const ScopedLock myScopedLock(objectLock);

    ui = component;
}

void TestoarResultsConsumer::unregisterUi(TestoarResultsComponent* component) {
    const ScopedLock myScopedLock(objectLock);

    if (ui == component) {
        ui = nullptr;
    }
}

void TestoarResultsConsumer::out(std::string s) {
    const ScopedLock myScopedLock(objectLock);

    if (ui != nullptr) {
        ui->resultsArriving(s);
    }
}

void TestoarResultsConsumer::err(std::string s) {
    const ScopedLock myScopedLock(objectLock);
    if (ui != nullptr) {
        ui->errorsArriving(s);
    }

}

