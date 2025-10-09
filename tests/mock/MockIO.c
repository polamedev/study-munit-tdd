/**
 * @file MockIO.c
 * @author polame (polame.dev@gmail.com)
 * @brief  Тестовый дублер мок
 * @date 2025-10-09
 */

#include <CppUTestExt/MockSupport_c.h>
#include <MyLib/IO.h>

void IO_Write(ioAddress addr, ioData data)
{
    mock_c()
        ->actualCall("IO_Write")
        ->withIntParameters("addr", addr)
        ->withIntParameters("data", data);
}

ioData IO_Read(ioAddress addr)
{
    mock_c()
        ->actualCall("IO_Read")
        ->withIntParameters("addr", addr);

    return mock_c()->returnValue().value.intValue;
}
