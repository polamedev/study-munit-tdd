#pragma once

#include <stdbool.h>

typedef struct CircularBuffer *CircularBuffer;

CircularBuffer CircularBuffer_create(int size);
CircularBuffer CircularBuffer_bufferedCreate(char buf[], int size);
void           CircularBuffer_destroy(CircularBuffer);

bool CircularBuffer_put(CircularBuffer, char);
void CircularBuffer_get(CircularBuffer);

bool CircularBuffer_isEmpty(CircularBuffer);

