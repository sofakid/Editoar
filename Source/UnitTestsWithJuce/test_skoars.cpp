#include "../jucer_headers.h"
#include "testing_util.hpp"

TEST_CASE ("Skoars", "[skoars]") {

    auto appData (File::getSpecialLocation (File::SpecialLocationType::userApplicationDataDirectory));
    REQUIRE (appData.exists ());

    auto testsDir (appData.getChildFile("skoar_tests"));

    INFO ("Tests folder");
    INFO (testsDir.getFullPathName ().toStdString ());

    REQUIRE (testsDir.exists ());

    Array<File> files;
    testsDir.findChildFiles (files, File::TypesOfFileToFind::findFiles, false, "*.skoar");

    for (auto file : files)
    {
        std::string filename (file.getFileNameWithoutExtension ().toStdString ());

        SECTION (filename) {
            std::string prefix ("SkoarUT<<");
            std::string suffix (">>SkoarUT");
            std::string utFilename (prefix + file.getFullPathName ().toStdString () + suffix);
            SkoarString skoarce (file.loadFileAsString().toWideCharPointer());

            INFO (filename);
            INFO (utFilename);
            run_skoar_test (skoarce);
        }
    }

}