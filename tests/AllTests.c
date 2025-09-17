#include "CircularBufferTest.h"

#include <stdio.h>



int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    printf("AllTest file\n");

    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */

    return munit_suite_main(&circularBufferTestSuite, (void *)"µnit", argc, argv);
}
