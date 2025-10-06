#include "ClockService.h"

#include <MillisService.h>

#include <memory.h>

#define MAX_SCHEDULE_EVENTS 10

typedef struct ScheduleEvent {
    ScheduleCallback callback;
    unsigned         period;
    unsigned         startTime;
} ScheduleEvent;

static struct {
    int           count;
    ScheduleEvent event;
    ScheduleEvent events[MAX_SCHEDULE_EVENTS];
} clockSchedule;

void ClockService_create()
{
    memset(&clockSchedule, 0, sizeof(clockSchedule));
    clockSchedule.count = 0;
}

void ClockService_destroy()
{
    clockSchedule.count = 0;
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
    clockSchedule.event.callback  = callback;
    clockSchedule.event.period    = mSecPeriod;
    clockSchedule.event.startTime = millis();

    ScheduleEvent *event;
    event            = &clockSchedule.events[clockSchedule.count];
    event->callback  = callback;
    event->period    = mSecPeriod;
    event->startTime = millis();

    clockSchedule.count++;
    return true;
}

static void processEvent(ScheduleEvent *event)
{
    if (event->period == 0) {
        return;
    }
    uint32_t mSec = millis();
    if (mSec - event->startTime >= event->period) {
        event->callback();
        event->startTime = mSec;
    }
}

void ClockService_call()
{
    for (int i = 0; i < clockSchedule.count; ++i)
    {
        processEvent(&clockSchedule.events[i]);
    }
}
