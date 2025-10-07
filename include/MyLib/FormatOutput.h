
/**
 * @brief  
 * Модуль для обертки функций стандартного вывода (printf)
 */

#pragma once

#ifdef __cplusplus 
extern "C" {
#endif

#include <stdarg.h>

int FormatOutput_print(const char *format, ...);

void FormatOutput_setPrintFunction(int (*printFunction)(const char *fmt, va_list va));
void FormatOutput_resetPrintFunction();


#ifdef __cplusplus
}
#endif