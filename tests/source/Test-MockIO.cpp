#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(MockIO) {
void setup()
{
}

void teardown()
{
}
}; // TEST_GROUP(MockIO)

TEST(MockIO, TestIO)
{
    int result = 1;

    LONGS_EQUAL(1, result);
}

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
