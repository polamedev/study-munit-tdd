#pragma once

#include <stddef.h>

void FormatOutputSpy_create(size_t len);
void FormatOutputSpy_destroy();

int         FormatOutputSpy_print(const char *format, ...);
const char *FormatOutputSpy_getOut();
