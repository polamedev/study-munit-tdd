#pragma once

#include <stdbool.h>

typedef struct CircularBuffer *CircularBuffer;

CircularBuffer CircularBuffer_Create(int size);
void           CircularBuffer_Destoy(CircularBuffer);

bool CircularBuffer_Put(CircularBuffer, char);
void CircularBuffer_Get(CircularBuffer);
