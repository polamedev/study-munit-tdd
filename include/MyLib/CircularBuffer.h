#pragma once

#include <stdbool.h>

typedef struct CircularBuffer *CircularBuffer;

CircularBuffer CircularBuffer_create(int size);
CircularBuffer CircularBuffer_bufferedCreate(char buf[], int size);
void           CircularBuffer_destroy(CircularBuffer);

bool CircularBuffer_put(CircularBuffer, char);
char CircularBuffer_get(CircularBuffer);

int CircularBuffer_count(const CircularBuffer);
int CircularBuffer_size(const CircularBuffer);

bool CircularBuffer_isEmpty(const CircularBuffer);

void CircularBuffer_print(const CircularBuffer);

typedef void(*PrintFormatter)();
void CircularBuffer_setPrintFormatter(CircularBuffer, PrintFormatter);
// TODO
