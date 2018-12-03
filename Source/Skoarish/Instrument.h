#pragma once

#include "../jucer_Headers.h"
#include <functional>

class SkoarishInstrument;
typedef std::function<void(SkoarishInstrument*)> SpellOfInstruments;

class SkoarishInstrument
{
public:
    SkoarishInstrument(String id);
    virtual ~SkoarishInstrument();
    String getId();

    static String makeValidId(String);
    static String makeValidUniqueId(String dirty);
 
protected:
    String id;
};

