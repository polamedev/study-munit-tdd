#include "MockMillisService.h"

#include <MillisService.h>

/*
Тестовый таргет будет использовать эту реализацию, а не реализацию из библиотеки

Важно необходимо переопределит все функции из исходного файла
*/

static uint32_t mock_msec = 0;

uint32_t millis()
{
    return mock_msec;
}


const char *MillisService_moduleInfo()
{
    return "MOCK Millis Service module";
}

void MockMillisService_setMillis(uint32_t msec)
{
    mock_msec = msec;
}
