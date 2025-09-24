/*

    ClockService - модуль который запускает зарегистрированные колбеки, когда настало время

    Функционал:
    - Регистрация колбеков с периодом вызова
    - Вызов колбеков при наступлении времени
    - Удаление зарегистрированного колбека по идентификационному номеру
    - Возврат периода вызова колбека по id
    - Возврат общего числа зарегистрированных колбеков
    - Возврат максимального количества возможных регистраций

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

#include <munit.h>

#include <stdio.h>

static MunitResult temp(const MunitParameter params[], void *user_data)
{

    return MUNIT_OK;
}

static MunitTest clockServiceTests[] = {
    {                "/temp", temp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    /* finalizer */

    {(char *)"no more tests", NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

MunitSuite clockServiceTestSuite = {
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
