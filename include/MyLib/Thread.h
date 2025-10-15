/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
 ***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct ThreadStruct *Thread;
typedef void *(*ThreadEntryFunction)(void *);

Thread Thread_Create(ThreadEntryFunction f, void *parameter);
void   Thread_Start(Thread);
void   Thread_Destroy(Thread);

void Thread_Join(Thread, void **result);

typedef struct ThreadMutexStruct *ThreadMutex;

ThreadMutex Thread_Mutex_Create();
void        Thread_Mutex_Destroy(ThreadMutex);
bool        Thread_Mutex_Lock(ThreadMutex);
bool        Thread_Mutex_Unlock(ThreadMutex);

void *Thread_Result(Thread);
void  MyOs_Init(int maxThreads);
void  MyOs_ShutDown(void);

#ifdef __cplusplus
}
#endif
