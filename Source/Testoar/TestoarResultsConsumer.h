#pragma once
#include "TestoarResultsComponent.h"

namespace TestoarResultsConsumer {

    void registerUi(TestoarResultsComponent* component);
    void unregisterUi(TestoarResultsComponent* component);

    void out(std::string s);
    void err(std::string s);

}