// cppcheck-suppress-file syntaxError

#include "CircularBuffer.h"

#include <munit.h>

#include <stdio.h>

/*
Функционал для кругового буфера

[_] Создание буфера определенного размера
[_] Уничтожение - под вопросом, когда буфер создается циклически
[_] Положить байт в буфер
[_] Взять байт в буфер
[_] Проверка Fifo
[_] Проверка на пуст
[_] Проверка на полон

*/

static MunitResult emptyAfterCreate(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(10);
    munit_assert_true(CircularBuffer_isEmpty(buffer));

    return MUNIT_OK;
}

static MunitResult notEmptyAfterPut(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(10);
    munit_assert_true(CircularBuffer_isEmpty(buffer));

    CircularBuffer_put(buffer, 1);

    munit_assert_true(!CircularBuffer_isEmpty(buffer));

    return MUNIT_OK;
}

static MunitResult putAndGetCharIsEqual(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(10);
    char           put    = 'a';
    CircularBuffer_put(buffer, put);
    char get;
    get = CircularBuffer_get(buffer);

    munit_assert_char(put, ==, get);
    return MUNIT_OK;
}

static MunitResult putAndGetSecondCharIsEqual(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(10);
    {
        char put = 'a';
        CircularBuffer_put(buffer, put);
        char get;
        get = CircularBuffer_get(buffer);
        munit_assert_char(put, ==, get);
    }

    {
        char put = 'b';
        CircularBuffer_put(buffer, put);
        char get;
        get = CircularBuffer_get(buffer);
        munit_assert_char(put, ==, get);
    }

    return MUNIT_OK;
}

static MunitResult checkOverWriteBuffer(const MunitParameter params[], void *user_data)
{
    const size_t size = 10;
    CircularBuffer buffer = CircularBuffer_create(size);

    const char in[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    for (int i = 0; i < sizeof(in); i++) {
        CircularBuffer_put(buffer, in[i]);
    }

    char get = CircularBuffer_get(buffer);

    munit_assert_char(in[sizeof(in) - size], ==, get);

    return MUNIT_OK;
}

static MunitTest circularBufferTests[] = {
    {          (char *)"/emptyAfterCreate",           emptyAfterCreate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {          (char *)"/notEmptyAfterPut",           notEmptyAfterPut, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {      (char *)"/putAndGetCharIsEqual",       putAndGetCharIsEqual, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/putAndGetSecondCharIsEqual", putAndGetSecondCharIsEqual, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {      (char *)"/checkOverWriteBuffer",       checkOverWriteBuffer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    /* finalizer */

    {              (char *)"no more tests",                       NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

MunitSuite circularBufferTestSuite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"/CircularBuffer",
    /* The first parameter is the array of test suites. */
    circularBufferTests,
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
