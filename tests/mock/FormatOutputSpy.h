#pragma once

#include <stdarg.h>
#include <stddef.h>

void FormatOutputSpy_create(size_t len);
void FormatOutputSpy_destroy();

/**
 * @brief
 * @param  format:
 * @param  ...:
 * @return int - Выводит число отображенных символов (0 вывод пустой строки ""),
 *         Выводит число < 0 в случае ошибки
 */
int FormatOutputSpy_print(const char *format, ...);

/**
 * @brief
 * @param format
 * @param va
 * @return
 */
int FormatOutputSpy_vprint(const char *format, va_list arguments);

const char *FormatOutputSpy_getOut();
