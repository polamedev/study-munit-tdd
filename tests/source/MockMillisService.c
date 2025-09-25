#include <MillisService.h>

/*
Тестовый таргет будет использовать эту реализацию, а не реализацию из библиотеки

Важно необходимо переопределит все функции из исходного файла
*/

int millis()
{
    return 1;
}


const char *MillisService_moduleInfo()
{
    return "MOCK Millis Service module";
}
