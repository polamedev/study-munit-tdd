//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved
//-    For use by owners of Test-Driven Development for Embedded C,
//-    and attendees of Renaissance Software Consulting, Co. training
//-    classes.
//-
//-    Available at http://pragprog.com/titles/jgade/
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3
//-
//-    Authorized users may use this source code in your own
//-    projects, however the source code may not be used to
//-    create training material, courses, books, articles, and
//-    the like. We make no guarantees that this source code is
//-    fit for any purpose.
//-
//-    www.renaissancesoftware.net james@renaissancesoftware.net
//- ------------------------------------------------------------------

#include <MyLib/Thread.h>
#include <MyLib/common.h>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

/*
Evolve MyOS to support Mutex and Event. A Mutex can
be acquired and released. One thread can wait for a signal from
another thread.
*/

static int   threadRan    = FALSE;
static int   threadResult = 42;
static void *threadEntry(void *p)
{
    (void)p;
    threadRan = TRUE;
    return &threadResult;
}

#if 0  
static int threadRan = FALSE;
static void * threadEntry(void * p)
{
    threadRan = TRUE;
    return 0;
}
#endif

TEST_GROUP(Thread) {
Thread thread;

void setup()
{
    threadRan = FALSE;
}

void teardown()
{
}
}; // TEST_GROUP(Thread)

TEST(Thread, CreateDoesNotStartThread)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Destroy(thread);
    CHECK(FALSE == threadRan);
}

TEST(Thread, StartedThreadRunsBeforeItIsDestroyed)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Destroy(thread);
    CHECK(TRUE == threadRan);
}

TEST(Thread, Join)
{
    void *result;
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Join(thread, &result);
    Thread_Destroy(thread);
    LONGS_EQUAL(42, *static_cast<int *>(result));
}

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
