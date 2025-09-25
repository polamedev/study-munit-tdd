#include "CircularBufferTest.h"
#include "ClockServiceTest.h"

#include <stdio.h>



int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    printf("AllTest file\n");

    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */
    munit_suite_main(&circularBufferTestSuite, (void *)"µnit", argc, argv);
    munit_suite_main(&clockServiceTestSuite, (void *)"µnit", argc, argv);

    return 0;
}
