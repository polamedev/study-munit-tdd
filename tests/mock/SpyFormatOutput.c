#include "SpyFormatOutput.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    char  *str;
    size_t size;
    int    writeSize;
} self;

void SpyFormatOutput_create(size_t size)
{
    self.str       = calloc(sizeof(char), size);
    self.size      = size;
    self.writeSize = 0;
}

void SpyFormatOutput_destroy()
{
    free(self.str);
    self.str = NULL;
}

int SpyFormatOutput_print(const char *format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    int written_size = SpyFormatOutput_vprint(format, arguments);
    va_end(arguments);

    return written_size;
}

int SpyFormatOutput_vprint(const char *format, va_list arguments)
{
    int written_size  = vsnprintf(&self.str[self.writeSize], self.size, format, arguments);
    self.writeSize   += written_size;
    return written_size;
}

const char *SpyFormatOutput_getOut()
{
    return self.str;
}

