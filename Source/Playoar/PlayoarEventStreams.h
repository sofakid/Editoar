#pragma once
#include "../Utility/concurrentqueue.h"
#include "skoar.hpp"

class PlayoarUiEvent
{
public:
    int i;

};

class PlayoarEventStreams
{
    moodycamel::ConcurrentQueue<SkoarEventPtr> skoarEvents;
    //.moodycamel::ConcurrentQueue<PlayoarUiEvent&> uiEvents;


};
