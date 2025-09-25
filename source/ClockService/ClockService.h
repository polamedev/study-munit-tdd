#pragma once

#include <stdbool.h>

typedef void (*ScheduleCallback)();

void ClockService_create();
void ClockService_destroy();
int  ClockService_count();
int  ClockService_size();
bool ClockService_schedule(ScheduleCallback callback, int mSecPeriod);

int  ClockService_millis();


