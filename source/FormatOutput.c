#include "FormatOutput.h"

#include <stdio.h>

static struct {
    int (*printFunction)(const char *fmt, va_list va);
} self = {
    .printFunction = vprintf,
};

int FormatOutput_print(const char *format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    int written_size = self.printFunction(format, arguments);
    va_end(arguments);
    return written_size;
}

int FormatOutput_vprint(const char *format, va_list va)
{
    return self.printFunction(format, va);
}

void FormatOutput_setPrintFunction(int (*printFunction)(const char *format, va_list arguments))
{
    self.printFunction = printFunction;
}

void FormatOutput_resetPrintFunction()
{
    self.printFunction = vprintf;
}
