// cppcheck-suppress-file syntaxError

#include <SpyFormatOutput.h>

#include <munit.h>
#include <stdio.h>

static void *setup(const MunitParameter params[], void *user_data)
{
    (void)user_data;
    SpyFormatOutput_create(200);
    return NULL;
}

static void tearDown(void *fixture)
{
    (void)fixture;
    SpyFormatOutput_destroy();
}

static MunitResult zeroOutAfterCreate(const MunitParameter params[], void *user_data)
{
    const char *str = SpyFormatOutput_getOut();
    munit_assert_int(strlen(str), ==, 0);
    return MUNIT_OK;
}

static MunitResult simplePrint(const MunitParameter params[], void *user_data)
{
    const char *out = "Hello world!";
    SpyFormatOutput_print("Hello world!");
    const char *str = SpyFormatOutput_getOut();
    munit_assert_string_equal(out, str);
    return MUNIT_OK;
}

static MunitResult checkRetval(const MunitParameter params[], void *user_data)
{
    const char *out        = "Hello world!";
    int         writeCount = SpyFormatOutput_print("Hello world!");
    munit_assert_int(strlen(out), ==, writeCount);
    return MUNIT_OK;
}

static MunitResult multiplyPrint(const MunitParameter params[], void *user_data)
{
    const char *in1        = "One";
    const char *in2        = "Two";
    int         writeCount = 0;

    writeCount += SpyFormatOutput_print(in1);
    writeCount += SpyFormatOutput_print(in2);

    munit_assert_string_equal(SpyFormatOutput_getOut(), "OneTwo");
    munit_assert_int(strlen(in1) + strlen(in2), ==, writeCount);
    return MUNIT_OK;
}

static MunitResult complexPrint(const MunitParameter params[], void *user_data)
{
    int writeCount = SpyFormatOutput_print("1 %i 2 %i 3 %i ", 1, 10, 100);

    munit_assert_string_equal(SpyFormatOutput_getOut(), "1 1 2 10 3 100 ");
    munit_assert_int(writeCount, ==, 15);
    return MUNIT_OK;
}

static MunitResult vprintSimpleTest(const MunitParameter params[], void *user_data)
{
    const char *out = "Hello world!";
    va_list     args;
    SpyFormatOutput_vprint(out, args);
    const char *str = SpyFormatOutput_getOut();
    munit_assert_string_equal(out, str);
    return MUNIT_OK;
}

static MunitResult vprintCheckRetval(const MunitParameter params[], void *user_data)
{
    const char *out = "Hello world!";
    va_list     args;
    int         writeCount = SpyFormatOutput_vprint(out, args);
    munit_assert_int(strlen(out), ==, writeCount);
    return MUNIT_OK;
}

static MunitResult vprintMultiplyPrint(const MunitParameter params[], void *user_data)
{
    const char *in1        = "One";
    const char *in2        = "Two";
    int         writeCount = 0;
    va_list     args;

    writeCount += SpyFormatOutput_vprint(in1, args);
    writeCount += SpyFormatOutput_vprint(in2, args);

    munit_assert_string_equal(SpyFormatOutput_getOut(), "OneTwo");
    munit_assert_int(strlen(in1) + strlen(in2), ==, writeCount);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {   "zeroOutAfterCreate",  zeroOutAfterCreate, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {          "simplePrint",         simplePrint, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {          "checkRetval",         checkRetval, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {        "multiplyPrint",       multiplyPrint, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {         "complexPrint",        complexPrint, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {     "vprintSimpleTest",    vprintSimpleTest, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {    "vprintCheckRetval",   vprintCheckRetval, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {  "vprintMultiplyPrint", vprintMultiplyPrint, setup, tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    /* finalizer */
    {(char *)"no more tests",                NULL,  NULL,     NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite testSuite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"",
    /* The first parameter is the array of test suites. */
    tests,
    /* In addition to containing test cases, suites can contain other
     * test suites.  This isn't necessary in this example, but it can be
     * a great help to projects with lots of tests by making it easier
     * to spread the tests across many files.  This is where you would
     * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
     * running multiple iterations of the tests.  This is usually only
     * interesting if you make use of the PRNG to randomize your tests
     * cases a bit, or if you are doing performance testing and want to
     * average multiple runs.  0 is an alias for 1. */
    1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    printf("--- SpyFormatOutput Test ---\n");

    // int s1 = printf("");
    // int s2 = printf("12345");
    // int s3 = printf(NULL);

    // printf("s1 = %i s2 = %i s3 = %i ", s1, s2, s3);

    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */

    return munit_suite_main(&testSuite, (void *)"µnit", argc, argv);
}
