#pragma once
#include "../jucer_Headers.h"
#include "skoar.hpp"
#include "minstrel.hpp"

class DebuggoarSession {
public:
    DebuggoarSession(String voice, Skoar* skoar);
    ~DebuggoarSession();

private:
    SkoarMinstrelPtr m;
};