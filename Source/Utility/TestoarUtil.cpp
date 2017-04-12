#include "TestoarUtil.h"

const String UnitTestsID ("Unit Tests");

File TestoarUtil::createUnitTest (Project & p, String testName, String skoarce) 
{
    auto group = createUnitTestsGroup (p);

    File file = createUnitTestFile (p, testName);
    file.replaceWithText (skoarce);
    file.appendText ("\n");

    group.addFileAtIndex (file, -1, false);
    return file;
}

Project::Item TestoarUtil::createUnitTestsGroup (Project & p)
{
    return p.getMainGroup ().getOrCreateSubGroup (UnitTestsID);
}

File TestoarUtil::createUnitTestFile (Project & p, String testName)
{
    String fileName = testName + String (".skoar");
    File folder (p.getProjectFolder ());

    String fullPath (File::addTrailingSeparator (folder.getFullPathName()) + fileName);

    return File (fullPath);
}
