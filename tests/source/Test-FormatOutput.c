
#include <munit.c>

/*
 - Установка функции вывода
 - Очистка функции вывода
*/

static MunitResult test(const MunitParameter params[], void *user_data)
{
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {"test", test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    /* finalizer */
    {     "no more tests", NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite testSuite = {"", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    printf("--- Test-FormatOutput ---\n");
    return munit_suite_main(&testSuite, (void *)"µnit", argc, argv);
}
