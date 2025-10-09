/**
 * @file MockIO.c
 * @author polame (polame.dev@gmail.com)
 * @brief  Тестовый дублер мок
 * @date 2025-10-09
 */

#include <CppUTestExt/MockSupport.h>
#include <MyLib/IO.h>
// #include "MockIO.h"


extern "C" {

void IO_Write(ioAddress addr, ioData data)
{
    mock()
        .actualCall("IO_Write")
        .withParameter("addr", addr)
        .withParameter("data", data);
}

ioData IO_Read(ioAddress addr)
{
    mock()
        .actualCall("IO_Read")
        .withParameter("addr", addr);

    return mock().returnValue().getIntValue();
}

}


