#pragma once

#include <stdarg.h>
#include <stddef.h>

void SpyFormatOutput_create(size_t len);
void SpyFormatOutput_destroy();

/**
 * @brief
 * @param  format:
 * @param  ...:
 * @return int - Выводит число отображенных символов (0 вывод пустой строки ""),
 *         Выводит число < 0 в случае ошибки
 */
int SpyFormatOutput_print(const char *format, ...);

/**
 * @brief
 * @param format
 * @param va
 * @return
 */
int SpyFormatOutput_vprint(const char *format, va_list arguments);

const char *SpyFormatOutput_getOut();
