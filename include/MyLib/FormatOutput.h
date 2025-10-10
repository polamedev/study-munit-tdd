
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

void FormatOutput_setVPrintFunction(int (*printFunction)(const char *format, va_list arguments));
void FormatOutput_resetVPrintFunction();

#ifdef __cplusplus
}
#endif
