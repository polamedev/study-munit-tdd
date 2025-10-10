/**
 * @file MockIO.c
 * @author polame (polame.dev@gmail.com)
 * @brief  Тестовый дублер мок
 * @date 2025-10-09
 */

#include "MockIO.hpp"

#include <CppUTestExt/MockSupport.h>
#include <MyLib/IO.h>

static SimpleString mockName = "";

extern "C" {

void IO_Write(ioAddress addr, ioData data)
{
    mock(mockName)
        .actualCall("IO_Write")
        .withParameter("addr", addr)
        .withParameter("data", data);
}

ioData IO_Read(ioAddress addr)
{
    mock(mockName)
        .actualCall("IO_Read")
        .withParameter("addr", addr);

    return mock(mockName).returnValue().getIntValue();
}
}

void MockIO_setup(const SimpleString &mockName, bool strictOrder)
{
    ::mockName = mockName;

    if (strictOrder) {
        mock(mockName).strictOrder();
    }
}

void MockIO_teardown()
{
    mockName = "";
}

void MockIO_expectRead(ioAddress add, ioData retData, unsigned int amount)
{
    mock(mockName).expectNCalls(amount, "IO_Read").withParameter("addr", add).andReturnValue((int)retData);
}

void MockIO_expectWrite(ioAddress add, ioData writeData, unsigned int amount)
{
    mock(mockName).expectNCalls(amount, "IO_Write").withParameter("addr", (int)add).withParameter("data", writeData);
}

void MockIO_checkExpectations()
{
    mock(mockName).checkExpectations();
}
