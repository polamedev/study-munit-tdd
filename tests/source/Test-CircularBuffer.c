// cppcheck-suppress-file syntaxError

#include <MyLib/CircularBuffer.h>
#include <MyLib/FormatOutput.h>

#include <SpyFormatOutput.h>

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

static char *increaseFillBuf(char *buf, int fill_size, char start_val)
{
    for (int i = 0; i < fill_size; ++i)
    {
        buf[i] = start_val;
        start_val++;
    }
}

static void putBuff(CircularBuffer cb, const char *putBuf, int size)
{
    for (int i = 0; i < size; ++i)
    {
        CircularBuffer_put(cb, putBuf[i]);
    }
}

static void getBuff(CircularBuffer cb, char *getBuf, int size)
{
    for (int i = 0; i < size; ++i)
    {
        getBuf[i] = CircularBuffer_get(cb);
    }
}

static int sprintBuff(char *s, char *buf, int size)
{
    int j = 0;

    j += sprintf(s + j, "Buff - ");
    for (int i = 0; i < size; ++i)
    {
        j += sprintf(s + j, "%i ", buf[i]);
    }
    j += sprintf(s + j, "\n");

    return j;
}

#define assertBuffIsEqual(buf1, buf2, size)                 \
    {                                                       \
        bool check = memcmp(buf1, buf2, size) == 0;         \
        if (!check) {                                       \
            int  j = 0;                                     \
            char s[100];                                    \
            j += sprintf(s + j, "Buffers is not equal:\n"); \
            j += sprintBuff(s + j, buf1, size);             \
            j += sprintBuff(s + j, buf2, size);             \
            munit_error(s);                                 \
        }                                                   \
    }

static void *setup(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(10);
    return buffer;
}

static void tearDown(void *fixture)
{
    CircularBuffer buffer = (CircularBuffer)fixture;
    CircularBuffer_destroy(buffer);
}

static MunitResult emptyAfterCreate(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;
    munit_assert_true(CircularBuffer_isEmpty(buffer));

    return MUNIT_OK;
}

static MunitResult notEmptyAfterPut(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;
    munit_assert_true(CircularBuffer_isEmpty(buffer));

    CircularBuffer_put(buffer, 1);

    munit_assert_true(!CircularBuffer_isEmpty(buffer));

    return MUNIT_OK;
}

static MunitResult putAndGetCharIsEqual(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;
    char           put    = 'a';
    CircularBuffer_put(buffer, put);
    char get;
    get = CircularBuffer_get(buffer);

    munit_assert_char(put, ==, 'a');
    return MUNIT_OK;
}

static MunitResult putAndGetSecondCharIsEqual(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;
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
    CircularBuffer buffer = user_data;
    const size_t   size   = CircularBuffer_size(buffer);

    const char in[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    putBuff(buffer, in, sizeof(in));

    char get = CircularBuffer_get(buffer);

    munit_assert_char(in[sizeof(in) - size], ==, get);

    return MUNIT_OK;
}

static MunitResult checkCountBuffer(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;

    munit_assert_int(0, ==, CircularBuffer_count(buffer));

    char in[] = {1, 2, 3};
    putBuff(buffer, in, sizeof(in));

    munit_assert_int(sizeof(in), ==, CircularBuffer_count(buffer));

    return MUNIT_OK;
}

static MunitResult checkOverWriteCountBuffer(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer   = user_data;
    const int      putCount = 15;
    int            size     = CircularBuffer_size(buffer);

    munit_assert_int(0, ==, CircularBuffer_count(buffer));

    for (int i = 0; i < putCount; ++i) {
        CircularBuffer_put(buffer, 3);
    }

    munit_assert_int(size, ==, CircularBuffer_count(buffer));

    return MUNIT_OK;
}

static MunitResult checkSize(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(15);
    munit_assert_int(15, ==, CircularBuffer_size(buffer));
    CircularBuffer_destroy(buffer);

    return MUNIT_OK;
}

static MunitResult checkFullWrite(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;

    char in[10];
    increaseFillBuf(in, sizeof(in), 0);
    putBuff(buffer, in, sizeof(in));

    char out[sizeof(in)];
    getBuff(buffer, out, sizeof(out));

    assertBuffIsEqual(in, out, sizeof(in));

    return MUNIT_OK;
}

static MunitResult checkReadOverWriteBuf(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;

    char in[23];
    increaseFillBuf(in, sizeof(in), 0);
    putBuff(buffer, in, sizeof(in));

    char out[7];
    getBuff(buffer, out, sizeof(out));

    char compare[sizeof(out)];
    increaseFillBuf(compare, sizeof(compare), sizeof(in) - CircularBuffer_size(buffer));

    assertBuffIsEqual(out, compare, sizeof(out));

    return MUNIT_OK;
}

static MunitResult checkCreationBigBuffer(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(50);

    char in[50];
    increaseFillBuf(in, sizeof(in), 0);
    putBuff(buffer, in, sizeof(in));

    char out[50];
    getBuff(buffer, out, sizeof(out));

    assertBuffIsEqual(in, out, sizeof(in));

    CircularBuffer_destroy(buffer);

    return MUNIT_OK;
}

static MunitResult checkCreationFewBuffer(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer1 = CircularBuffer_create(10);
    CircularBuffer buffer2 = CircularBuffer_create(20);

    char in1[10];
    char out1[10];
    char in2[20];
    char out2[20];

    increaseFillBuf(in1, sizeof(in1), 0);
    increaseFillBuf(in2, sizeof(in2), 55);

    putBuff(buffer1, in1, sizeof(in1));
    putBuff(buffer2, in2, sizeof(in2));

    getBuff(buffer1, out1, sizeof(out1));
    assertBuffIsEqual(in1, out1, sizeof(in1));

    getBuff(buffer2, out2, sizeof(out2));
    assertBuffIsEqual(in2, out2, sizeof(in2));

    CircularBuffer_destroy(buffer1);
    CircularBuffer_destroy(buffer2);

    return MUNIT_OK;
}

static void *formattedSetup(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = CircularBuffer_create(20);
    SpyFormatOutput_create(200);
    FormatOutput_setPrintFunction(SpyFormatOutput_vprint);

    return buffer;
}

static void formattedTearDown(void *fixture)
{
    FormatOutput_resetPrintFunction();
    SpyFormatOutput_destroy();

    CircularBuffer buffer = (CircularBuffer)fixture;
    CircularBuffer_destroy(buffer);
}

MunitResult checkBufferPrint(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;

    char in[10];
    increaseFillBuf(in, sizeof(in), 1);
    putBuff(buffer, in, sizeof(in));
    CircularBuffer_put(buffer, 0);
    CircularBuffer_put(buffer, 0);

    CircularBuffer_print(buffer);
    const char *out = SpyFormatOutput_getOut();

    static const char *compare = "1   2   3   4   5\n6   7   8   9  10\n0   0";
    munit_assert_string_equal(out, compare);

    return MUNIT_OK;
}

MunitResult bufferPrint2(const MunitParameter params[], void *user_data)
{
    CircularBuffer buffer = user_data;

    static const char in[] = {1, 2, 3, 250, 1, 2, 3};
    putBuff(buffer, in, sizeof(in));

    CircularBuffer_print(buffer);
    const char *out = SpyFormatOutput_getOut();

    munit_assert_string_equal(out, "compare");

    return MUNIT_OK;
}

static MunitTest tests[] = {
    {      "emptyAfterCreate",           emptyAfterCreate,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {      "notEmptyAfterPut",           notEmptyAfterPut,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {  "putAndGetCharIsEqual",       putAndGetCharIsEqual,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {   "putAndGetSecondChar", putAndGetSecondCharIsEqual,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {  "checkOverWriteBuffer",       checkOverWriteBuffer,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {            "checkCount",           checkCountBuffer,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {             "checkSize",                  checkSize,           NULL,              NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {        "checkFullWrite",             checkFullWrite,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    { "checkReadOverWriteBuf",      checkReadOverWriteBuf,          setup,          tearDown, MUNIT_TEST_OPTION_NONE, NULL},
    {"checkCreationBigBuffer",     checkCreationBigBuffer,           NULL,              NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"checkCreationFewBuffer",     checkCreationFewBuffer,           NULL,              NULL, MUNIT_TEST_OPTION_NONE, NULL},

    /* print */
    {           "bufferPrint",           checkBufferPrint, formattedSetup, formattedTearDown, MUNIT_TEST_OPTION_NONE, NULL},

    /* finalizer */
    {         "no more tests",                       NULL,           NULL,              NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite testSuite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    "",
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
    printf("--- Test-CircularBuffer ---\n");

    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */

    return munit_suite_main(&testSuite, (void *)"µnit", argc, argv);
}
