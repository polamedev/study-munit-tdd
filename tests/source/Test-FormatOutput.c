// cppcheck-suppress-file syntaxError

#include <MyLib/FormatOutput.h>

#include <munit.c>

/*
 - Установка функции вывода
 - Очистка функции вывода
*/

static MunitResult test(const MunitParameter params[], void *user_data)
{
    (void) user_data;
    return MUNIT_OK;
}


int call_count = 0;
int testPrint(const char *fmt, va_list va)
{
    call_count++;
    return 0;
};

static void *setup(const MunitParameter params[], void *user_data)
{
    call_count = 0;
    return NULL;
}

static MunitResult zeroCallWithoutSetting(const MunitParameter params[], void *user_data)
{
    FormatOutput_print("");

    munit_assert_int(call_count, ==,  0);

    return MUNIT_OK;
}

static MunitResult testSetFormatFunction(const MunitParameter params[], void *user_data)
{
    (void) user_data;

    FormatOutput_setPrintFunction(testPrint);
    FormatOutput_print("");

    munit_assert_int(call_count, ==,  1);

    return MUNIT_OK;
}

static MunitResult zeroCallAfterReset(const MunitParameter params[], void *user_data)
{
    FormatOutput_setPrintFunction(testPrint);
    FormatOutput_resetPrintFunction();
    FormatOutput_print("");

    munit_assert_int(call_count, ==,  0);
}

static MunitTest tests[] = {
    {"test", test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"test Set Format Function", zeroCallWithoutSetting, setup, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"test Set Format Function", testSetFormatFunction, setup, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"test Set Format Function", zeroCallAfterReset, setup, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    /* finalizer */
    {     "no more tests", NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite testSuite = {"", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    printf("--- Test-FormatOutput ---\n");
    return munit_suite_main(&testSuite, (void *)"µnit", argc, argv);
}
