#include "CircularBuffer.h"

#include <stddef.h>

struct CircularBuffer {
    char *buf;
    int   size;
    int   head;
    int   tail;
};

struct CircularBuffer staticBuffer;

CircularBuffer
CircularBuffer_create(int size)
{
    staticBuffer.size = size;
    staticBuffer.head = 0;
    staticBuffer.tail = 0;
    return &staticBuffer;
}

CircularBuffer CircularBuffer_bufferedCreate(char buf[], int size)
{
    return &staticBuffer;
}

bool CircularBuffer_put(CircularBuffer buffer, char ch)
{
    buffer->head++;

    return false;
}

char CircularBuffer_get(CircularBuffer)
{
    return 'a';
}

bool CircularBuffer_isEmpty(CircularBuffer buffer)
{
    return buffer->head == buffer->tail;
}
