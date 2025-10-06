#pragma once

#include <stdbool.h>

typedef void (*TaskSchedule_Func)();

/**
 * @brief  Создать сервис периодического вызова функций
 */
void TaskSchedule_Create();
void TaskSchedule_Destroy();
int  TaskSchedule_Count();
int  TaskSchedule_Size();
bool TaskSchedule_Schedule(TaskSchedule_Func callback, int mSecPeriod);

/**
 * @brief  Функция периодического вызова сервиса (таска)
 *         Должна вызываться по таймеру
 */
void TaskSchedule_Call();
