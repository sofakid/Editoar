#include "../jucer_Headers.h"
#include "testing_util.hpp"

enum should_test_memory
{
    dont_test_memory = 0,
    do_test_memory
};

enum should_run_skoar
{
    dont_run_skoar = 0,
    do_run_skoar
};


void test_skoars (std::string file_prefix, should_test_memory should_test_memories, should_run_skoar should_run) {

    auto appData (File::getSpecialLocation (File::SpecialLocationType::userApplicationDataDirectory));
    REQUIRE (appData.exists ());

    auto testsDir (appData.getChildFile ("skoar_tests"));

    INFO ("Tests folder");
    INFO (testsDir.getFullPathName ().toStdString ());

    REQUIRE (testsDir.exists ());

    Array<File> files;
    testsDir.findChildFiles (files, File::TypesOfFileToFind::findFiles, false, "*.skoar");

    for (auto file : files)
    {
        std::string filename (file.getFileNameWithoutExtension ().toStdString ());

        if (filename.find (file_prefix) != 0U)
            continue;

        std::string prefix ("SkoarUT<<");
        std::string suffix (">>SkoarUT");
        std::string utFilename (prefix + file.getFullPathName ().toStdString () + suffix);
        SkoarString skoarce (file.loadFileAsString ().toWideCharPointer ());

        INFO (filename);
        INFO (utFilename);


        if (should_run)
            run_skoar_multi_test (skoarce, filename);
        else
        {
            if (should_test_memories)
            {
#if SKOAR_DEBUG_MEMORY
                SECTION (filename) {
                    reset_memories ();
                    compile_skoar_test (skoarce);
                    require_no_memory_consumed ();
                }
#endif
            }
        }
    }

}


TEST_CASE ("Elementary Structural", "[elementary_struct]") {
    test_skoars ("elem_struct_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Elementary Musical", "[elementary_mus]") {
    test_skoars ("elem_mus_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Intermediate", "[intermediate]") {
    test_skoars ("intermediate_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Dev Functionality", "[dev]") {
    test_skoars ("dev_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Msgs - Int", "[msgs]") {
    test_skoars ("msg_int_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Msgs - Float", "[msgs]") {
    test_skoars ("msg_float_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Msgs - List", "[msgs]") {
    test_skoars ("msg_list_", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

// --- Operators -------------------------------------------------
//
// These are separated into so many, because there is some kind of O(n^2) unhappiness
// happening when a test case is too large. It takes minutes and minutes to run.
//
TEST_CASE ("ops_cmp", "[ops], [ops-cmp]") {
    test_skoars ("ops_cmp", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_misc", "[ops], [ops-add], [ops-mul]") {
    test_skoars ("ops_misc", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_add_Int", "[ops], [ops-add]") { 
    test_skoars ("ops_add_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_add_Float", "[ops], [ops-add]") {
    test_skoars ("ops_add_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_add_Hash", "[ops], [ops-add]") {
    test_skoars ("ops_add_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("ops_sub_Int", "[ops], [ops-sub]") {
    test_skoars ("ops_sub_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_sub_Float", "[ops], [ops-sub]") {
    test_skoars ("ops_sub_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_sub_Hash", "[ops], [ops-sub]") {
    test_skoars ("ops_sub_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_mul_Int", "[ops], [ops-mul]") {
    test_skoars ("ops_mul_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_mul_Float", "[ops], [ops-mul]") {
    test_skoars ("ops_mul_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_mul_Hash", "[ops], [ops-mul]") {
    test_skoars ("ops_mul_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_div_Int", "[ops], [ops-div]") {
    test_skoars ("ops_div_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_div_Float", "[ops], [ops-div]") {
    test_skoars ("ops_div_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("ops_div_Hash", "[ops], [ops-div]") {
    test_skoars ("ops_div_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

// --- Memories --------------------------------------------------

#if SKOAR_DEBUG_MEMORY



TEST_CASE ("Memories - Compiled - Elementary Structural", "[memory]") {
    test_skoars ("elem_struct_", should_test_memory::do_test_memory, should_run_skoar::dont_run_skoar);
}

TEST_CASE ("Memories - Ran - Elementary Structural", "[memory]") {
    test_skoars ("elem_struct_", should_test_memory::do_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - Elementary Musical", "[memory]") {
    test_skoars ("elem_mus_", should_test_memory::do_test_memory, should_run_skoar::dont_run_skoar);
}

TEST_CASE ("Memories - Ran - Elementary Musical", "[memory]") {
    test_skoars ("elem_mus_", should_test_memory::do_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Memories - Compiled - Intermediate", "[memory]") {
    test_skoars ("intermediate_", should_test_memory::do_test_memory, should_run_skoar::dont_run_skoar);
}

TEST_CASE ("Memories - Ran - Intermediate", "[memory]") {
    test_skoars ("intermediate_", should_test_memory::do_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Dev Memories - Compiled", "[dev]") {
    test_skoars ("dev_", should_test_memory::do_test_memory, should_run_skoar::dont_run_skoar);
}

TEST_CASE ("Dev Memories - Ran", "[dev]") {
    test_skoars ("dev_", should_test_memory::do_test_memory, should_run_skoar::do_run_skoar);
}



// ------ Ops Memories -----------------------------------------
TEST_CASE ("Memories - Compiled - ops_misc", "[memory]") {
    test_skoars ("ops_misc", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_add_Int", "[memory]") {
    test_skoars ("ops_add_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_add_Float", "[memory]") {
    test_skoars ("ops_add_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_add_Hash", "[memory]") {
    test_skoars ("ops_add_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_sub_Int", "[memory]") {
    test_skoars ("ops_sub_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_sub_Float", "[memory]") {
    test_skoars ("ops_sub_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_sub_Hash", "[memory]") {
    test_skoars ("ops_sub_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_mul_Int", "[memory]") {
    test_skoars ("ops_mul_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_mul_Float", "[memory]") {
    test_skoars ("ops_mul_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_mul_Hash", "[memory]") {
    test_skoars ("ops_mul_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_div_Int", "[memory]") {
    test_skoars ("ops_div_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_div_Float", "[memory]") {
    test_skoars ("ops_div_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Compiled - ops_div_Hash", "[memory]") {
    test_skoars ("ops_div_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}


TEST_CASE ("Memories - Ran - ops_misc", "[memory]") {
    test_skoars ("ops_misc", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_add_Int", "[memory]") {
    test_skoars ("ops_add_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_add_Float", "[memory]") {
    test_skoars ("ops_add_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_add_Hash", "[memory]") {
    test_skoars ("ops_add_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_sub_Int", "[memory]") {
    test_skoars ("ops_sub_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_sub_Float", "[memory]") {
    test_skoars ("ops_sub_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_sub_Hash", "[memory]") {
    test_skoars ("ops_sub_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_mul_Int", "[memory]") {
    test_skoars ("ops_mul_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_mul_Float", "[memory]") {
    test_skoars ("ops_mul_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_mul_Hash", "[memory]") {
    test_skoars ("ops_mul_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_div_Int", "[memory]") {
    test_skoars ("ops_div_Int", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_div_Float", "[memory]") {
    test_skoars ("ops_div_Float", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

TEST_CASE ("Memories - Ran - ops_div_Hash", "[memory]") {
    test_skoars ("ops_div_Hash", should_test_memory::dont_test_memory, should_run_skoar::do_run_skoar);
}

#endif


