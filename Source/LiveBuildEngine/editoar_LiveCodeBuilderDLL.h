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

#ifndef EDITOAR_LIVECODEBUILDERDLL_H_INCLUDED
#define EDITOAR_LIVECODEBUILDERDLL_H_INCLUDED


extern "C"
{
    typedef void* LiveCodeBuilder;
    typedef bool (*SendMessageFunction) (void* userInfo, const void* data, size_t dataSize);
    typedef void (*CrashCallbackFunction) (const char* crashDescription);
    typedef void (*QuitCallbackFunction)();
    typedef void (*SetPropertyFunction) (const char* key, const char* value);
    typedef void (*GetPropertyFunction) (const char* key, char* value, size_t size);
    typedef void (*LoginCallbackFunction) (void* userInfo, const char* errorMessage, const char* username, const char* apiKey);

    // We've used an X macro to define the DLL functions rather than just declaring them, so that
    // we can load the DLL and its functions dynamically and cope with it not being there.
    // The CompileEngineDLL class is a wrapper that manages finding/loading the DLL and exposing
    // these as callable functions.
    #define LIVE_DLL_FUNCTIONS(X) \
        X (editoar_getVersion,     int, ()) \
        X (editoar_initialise,     void, (CrashCallbackFunction, QuitCallbackFunction, SetPropertyFunction, GetPropertyFunction, bool setupSignals)) \
        X (editoar_shutdown,       void, ()) \
        X (editoar_createBuilder,  LiveCodeBuilder, (SendMessageFunction, void* userInfo, const char* projectID, const char* cacheFolder)) \
        X (editoar_sendMessage,    void, (LiveCodeBuilder, const void* messageData, size_t messageDataSize)) \
        X (editoar_deleteBuilder,  void, (LiveCodeBuilder)) \
        X (editoar_login,          void, (const char* userLoginName, const char* userPassword, bool remainLoggedIn, LoginCallbackFunction, void* callbackUserInfo)) \
        X (editoar_logout,         void, ()) \
        X (editoar_isLoggedIn,     bool, ()) \
        X (editoar_getLoginName,   void, (char*)) \
        X (editoar_hasLicense,     bool, (const char* featureName)) \
        X (editoar_hasLiveCodingLicence, bool, ())

}


#endif  // EDITOAR_LIVECODEBUILDERDLL_H_INCLUDED
