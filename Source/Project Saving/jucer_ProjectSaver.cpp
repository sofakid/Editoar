/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#include "../jucer_Headers.h"
#include "jucer_ProjectSaver.h"

//==============================================================================
namespace
{
    inline int countMaxPluginChannels (const String& configString, bool isInput)
    {
        StringArray configs;
        configs.addTokens (configString, ", {}", StringRef());
        configs.trim();
        configs.removeEmptyStrings();
        jassert ((configs.size() & 1) == 0);  // looks like a syntax error in the configs?

        int maxVal = 0;
        for (int i = (isInput ? 0 : 1); i < configs.size(); i += 2)
            maxVal = jmax (maxVal, configs[i].getIntValue());

        return maxVal;
    }

    inline String valueToBool (const Value& v)
    {
        return static_cast<bool> (v.getValue()) ? "1" : "0";
    }

    inline String valueToStringLiteral (const var& v)
    {
        return CppTokeniserFunctions::addEscapeChars (v.toString()).quoted();
    }

    inline String valueToCharLiteral (const var& v)
    {
        String fourCharCode = v.toString().trim().substring (0, 4);
        uint32 hexRepresentation = 0;

        for (int i = 0; i < 4; ++i)
            hexRepresentation = (hexRepresentation << 8U)
                             |  (static_cast<unsigned int> (fourCharCode[i]) & 0xffU);

        return String ("0x") + String::toHexString (static_cast<int> (hexRepresentation))
                             + String (" // ")
                             + CppTokeniserFunctions::addEscapeChars (fourCharCode).quoted ('\'');
    }
}
