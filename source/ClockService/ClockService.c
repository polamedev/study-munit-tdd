#include "ClockService.h"

#include <MillisService.h>

typedef struct ScheduleEvent {
    ScheduleCallback callback;
    unsigned         period;
    unsigned         startTime;
} ScheduleEvent;

static struct {
    int           count;
    ScheduleEvent event;
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
    clockSchedule.event.callback  = callback;
    clockSchedule.event.period    = mSecPeriod;
    clockSchedule.event.startTime = millis();
    return true;
}

void ClockService_call()
{
    uint32_t mSec = millis();
    if (mSec - clockSchedule.event.startTime >= clockSchedule.event.period) {
        clockSchedule.event.callback();
        clockSchedule.event.startTime = mSec;
    }
}
