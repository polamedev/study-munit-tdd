#include "FormatOutputSpy.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    char  *str;
    size_t size;
    int    writeSize;
} self;

void FormatOutputSpy_create(size_t size)
{
    self.str       = calloc(sizeof(char), size);
    self.size      = size;
    self.writeSize = 0;
}

void FormatOutputSpy_destroy()
{
    free(self.str);
    self.str = NULL;
}

int FormatOutputSpy_print(const char *format, ...)
{
    int     written_size;
    va_list arguments;
    va_start(arguments, format);
    written_size = vsnprintf(&self.str[self.writeSize],
                             self.size, format, arguments);

    va_end(arguments);

    self.writeSize += written_size;

    return written_size;
}

const char *FormatOutputSpy_getOut()
{
    return self.str;
}

