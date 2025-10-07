
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
int FormatOutput_vprint(const char *format, va_list va);

void FormatOutput_setPrintFunction(int (*printFunction)(const char *format, va_list va));
void FormatOutput_resetPrintFunction();


#ifdef __cplusplus
}
#endif