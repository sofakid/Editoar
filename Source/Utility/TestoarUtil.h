#pragma once

#include "../jucer_Headers.h"
#include "../Project/jucer_Project.h"
#include "../Project/jucer_ProjectType.h"
#include "../Project Saving/jucer_ProjectSaver.h"
#include "../Application/jucer_OpenDocumentManager.h"
#include "../Application/jucer_Application.h"

namespace TestoarUtil
{
    File createUnitTest (Project & p, String testName, String skoarce);
    Project::Item createUnitTestsGroup (Project & p);
    File createUnitTestFile (Project & p, String testName);
}
