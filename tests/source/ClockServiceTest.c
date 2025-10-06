// cppcheck-suppress-file syntaxError

/*

    ClockService - модуль который запускает зарегистрированные колбеки, когда настало время

    Функционал:
    - Регистрация колбеков с периодом вызова
    - Вызов колбеков при наступлении времени
    - Удаление зарегистрированного колбека по идентификационному номеру
    - Возврат периода вызова колбека по id
    + Возврат общего числа зарегистрированных колбеков
    + Возврат максимального количества возможных регистраций

    тесты:
    - Создание clockService
    - Удаление clockService
    - После создания

    - После создания не должно быть зарегистрированных колбеков
    - При регистрации колбека должно быть возвращено число правильное число

    - Вызов колбека при наступлении времени
    - Вызов несколько раз колбека при нескольких наступлений колбеков
    - Вызов нескольких колбеков
    - Вызов нескольких колбеков при наступлении нескольких времен

*/

#include <ClockService.h>

#include "MockMillisService.h"

#include <munit.h>

#include <stdio.h>

int callbackCount = 0;

static void testCallback()
{
    callbackCount++;
}

//////////////////////////////////////////////////////////

static void *testSetup(const MunitParameter params[], void *user_data)
{
    callbackCount = 0;
    ClockService_create();
    MockMillisService_setMillis(0);
    return NULL;
}
static void testTearDown(void *fixture)
{
    ClockService_destroy();
}

////////////////////////////////////////////////////////////////////

static MunitResult emptyAfterCreate(const MunitParameter params[], void *user_data)
{
    munit_assert_int(ClockService_count(), ==, 0);
    return MUNIT_OK;
}

static MunitResult notZeroSizeAfterCreate(const MunitParameter params[], void *user_data)
{
    munit_assert_int(ClockService_size(), !=, 0);
    return MUNIT_OK;
}

static MunitResult notEmptyAfterSchedule(const MunitParameter params[], void *user_data)
{
    ClockService_schedule(testCallback, 100);
    munit_assert_int(ClockService_count(), !=, 0);
    return MUNIT_OK;
}

static MunitResult scheduleButItsNotTimeYet(const MunitParameter params[], void *user_data)
{
    ClockService_schedule(testCallback, 100);
    ClockService_call();

    munit_assert_int(callbackCount, ==, 0);
    return MUNIT_OK;
}

static MunitResult scheduleAndItsTime(const MunitParameter params[], void *user_data)
{
    ClockService_schedule(testCallback, 100);
    MockMillisService_setMillis(100);
    ClockService_call();

    munit_assert_int(callbackCount, ==, 1);
    return MUNIT_OK;
}

static MunitTest clockServiceTests[] = {
    {        "/emptyAfterCreate",         emptyAfterCreate, testSetup, testTearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {  "/notZeroSizeAfterCreate",   notZeroSizeAfterCreate, testSetup, testTearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {   "/notEmptyAfterSchedule",    notEmptyAfterSchedule, testSetup, testTearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {"/scheduleButItsNotTimeYet", scheduleButItsNotTimeYet, testSetup, testTearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {"/scheduleButItsNotTimeYet",       scheduleAndItsTime, testSetup, testTearDown, MUNIT_TEST_OPTION_NONE, NULL},

    /* finalizer */
    {    (char *)"no more tests",                     NULL,      NULL,         NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite clockServiceTestSuite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"/ClockService",
    /* The first parameter is the array of test suites. */
    clockServiceTests,
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
    printf("Millis Lib: %s\n", MillisService_moduleInfo());

    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */

    return munit_suite_main(&clockServiceTestSuite, (void *)"µnit", argc, argv);
    ;
}
