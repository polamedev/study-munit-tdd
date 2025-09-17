#include "CircularBuffer.h"

#include <stddef.h>
#include <stdio.h>

struct CircularBuffer {
    char *buf;
    int   size;
    int   head;
    int   tail;
    int   cnt;
};

static char staticBuffer[10];
struct CircularBuffer staticCircularBuffer;


static void printPuffer(CircularBuffer buffer)
{
    printf("size = %i; count = %i; ", buffer->size, buffer->cnt);

    for (int i = 0; i < buffer->size; ++i)
    {
        printf("%i ", buffer->buf[i]);
    }
    printf("\n");
}

CircularBuffer CircularBuffer_create(int size)
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

void CircularBuffer_destroy(CircularBuffer)
{
}

static int nextIndex(int *index, int size)
{
    (*index)++;
    if (*index == size) {
        *index = 0;
    }
    return *index;
}

bool CircularBuffer_put(CircularBuffer buffer, char ch)
{
    buffer->buf[buffer->head] = ch;
    buffer->cnt++;
    nextIndex(&buffer->head, buffer->size);

    if (buffer->cnt > buffer->size)
    {
        buffer->cnt--;
        nextIndex(&buffer->tail, buffer->size);
    }

    return false;
}

char CircularBuffer_get(CircularBuffer buffer)
{
    char ch = buffer->buf[buffer->tail];
    nextIndex(&buffer->tail, buffer->size);
    return ch;
}

int CircularBuffer_count(const CircularBuffer buffer)
{
    return buffer->cnt;
}

int CircularBuffer_size(const CircularBuffer buffer)
{
    return buffer->size;
}

bool CircularBuffer_isEmpty(const CircularBuffer buffer)
{
    return buffer->head == buffer->tail;
}
