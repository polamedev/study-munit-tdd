#include "CircularBuffer.h"

#include "FormatOutput.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct CircularBuffer {
    char *buf;
    int   size;
    int   head; // Индекс головы
    int   tail; // Индекс хвоста
    int   cnt;  // Число элементов в буфере
};

static char           staticBuffer[10];
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
    CircularBuffer cb = calloc(sizeof(CircularBuffer), 1);
    cb->size          = size;
    cb->head          = 0;
    cb->tail          = 0;
    cb->buf           = calloc(sizeof(char), size);
    return cb;
}

CircularBuffer CircularBuffer_bufferedCreate(char buf[], int size)
{
    (void)buf;
    return &staticCircularBuffer;
}

void CircularBuffer_destroy(CircularBuffer cb)
{
    free(cb->buf);
    free(cb);
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

static void printWhiteSpaces(int whiteNumber)
{
    for (int i = 0; i < whiteNumber; ++i) {
        FormatOutput_print(" ");
    }
}

static int getDigitalNumber(int number)
{
    int i = 0;

    while (number = number / 10)
    {
        i++;
    }
    return i;
}

void CircularBuffer_print(const CircularBuffer buffer)
{
    static const int MAX_ITEM_NUMBER_IN_STRING = 5;

    int i                  = buffer->tail;
    int itemNumberInString = 0;
    FormatOutput_print("%i", buffer->buf[i]);
    nextIndex(&i, buffer->size);
    ++itemNumberInString;
    for (; i != buffer->head; nextIndex(&i, buffer->size), ++itemNumberInString) {
        char number = buffer->buf[i];

        if (itemNumberInString < MAX_ITEM_NUMBER_IN_STRING) {
            int digitNum = getDigitalNumber(number);
            printWhiteSpaces(3 - digitNum);
            FormatOutput_print("%i", number);
        }
        else {
            FormatOutput_print("\n%i", number);
            itemNumberInString = 0;
        }
    }
}
