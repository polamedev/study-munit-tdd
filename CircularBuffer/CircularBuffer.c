#include "CircularBuffer.h"

#include <stddef.h>

struct CircularBuffer {
    char *buf;
    int   size;
    int   head;
    int   tail;
};

struct CircularBuffer staticCircularBuffer;

static char staticBuffer[10];

CircularBuffer
CircularBuffer_create(int size)
{
    staticCircularBuffer.size = size;
    staticCircularBuffer.head = 0;
    staticCircularBuffer.tail = 0;
    staticCircularBuffer.buf  = staticBuffer;
    return &staticCircularBuffer;
}

CircularBuffer CircularBuffer_bufferedCreate(char buf[], int size)
{
    return &staticCircularBuffer;
}

bool CircularBuffer_put(CircularBuffer buffer, char ch)
{
    buffer->buf[buffer->head] = ch;
    buffer->head++;
    if (buffer->head == buffer->size) {
        buffer->head = 0;
    }

    return false;
}

char CircularBuffer_get(CircularBuffer buffer)
{
    return buffer->buf[buffer->tail++];
}

bool CircularBuffer_isEmpty(CircularBuffer buffer)
{
    return buffer->head == buffer->tail;
}
