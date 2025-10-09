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

void MockIO_create(const SimpleString &mockName)
{
    ::mockName = mockName;
}

void MockIO_destroy()
{
    mockName = "";
}
