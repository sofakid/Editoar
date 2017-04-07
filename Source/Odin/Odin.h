#pragma once
#include "skoar.hpp"
#include "../Debuggoar/DebuggoarComponent.h"
#include "../Debuggoar/DebuggoarDeetsPanel.h"
#include "../Debuggoar/SkoarpionsComponent.h"

namespace Odin {

    void setSkoar(Skoar*);
    Skoar* getSkoar();

    DebuggoarComponent* getDebuggoar();
    DebuggoarDeets* getDeets();
    SkoarpionsComponent* getSkoarpionsComponent();
    
    void setDebuggoar(DebuggoarComponent*);
    void setDeets(DebuggoarDeets*);
    void setSkoarpionsComponent(SkoarpionsComponent*);

};