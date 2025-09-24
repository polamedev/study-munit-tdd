#include "ClockService.h"

static struct {
    int count;
} clockSchedule;

void ClockService_create()
{
    clockSchedule.count = 0;
}

void ClockService_destroy()
{
}

int ClockService_count()
{
    return clockSchedule.count;
}

int ClockService_size()
{
    return 10;
}

bool ClockService_schedule(ScheduleCallback callback, int mSecPeriod)
{
    clockSchedule.count++;
    return true;
}

