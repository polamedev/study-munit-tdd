extern "C" {
#include <MyLib/IO.h>
}

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

TEST_GROUP(MockIO) {
void setup()
{
}

void teardown()
{
    mock().checkExpectations();
    mock().clear();
}
}; // TEST_GROUP(MockIO)

TEST(MockIO, TestIO)
{
    int result = 1;

    LONGS_EQUAL(1, result);
}

TEST(MockIO, ExceptRead)
{
    ioAddress addr = 0x1;
    ioData    data = 0x2;

    /* Задаем ожидание вызова функции IO_Read с параметром "addr" и возвращаемым значение data */
    mock()
        .expectOneCall("IO_Read")
        .withParameter("addr", addr)
        .andReturnValue((int)data);

    ioData result = IO_Read(addr);

    LONGS_EQUAL(data, result);
}

TEST(MockIO, ExceptWrite)
{
    ioAddress addr = 0x1;
    ioData    data = 0x2;

    /* Задаем ожидание вызова функции IO_Write с двумя параметрами */
    mock()
        .expectOneCall("IO_Write")
        .withParameter("addr", addr)
        .withParameter("data", data);

    IO_Write(addr, data);
}

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
