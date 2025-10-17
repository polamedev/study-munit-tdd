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

#include "LightDriverSpy.h"

#include <MyLib/devices/LightDriverPrivate.h>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

static int callCount   = 0;
static int globalLight = 0;

static void incrementCall(LightDriver self)
{
    (void)self;
    callCount++;
}

static void setLight(LightDriver self, int light)
{
    (void)self;
    globalLight = light;
}

LightDriverInterfaceStruct incrementCalls = {incrementCall, incrementCall, incrementCall, setLight};

LightDriverStruct testDriver = {
    &incrementCalls,
    "testDriver",
    13,
};

TEST_GROUP(LightDriver) {
void setup()
{
}

void teardown()
{
    callCount   = 0;
    globalLight = 0;
}
}; // TEST_GROUP(LightDriver)

TEST(LightDriver, NullDriverDoesNoHarm)
{
    // Вызов пустого драйвера не должен сломаться
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
}

TEST(LightDriver, Accessors)
{
    LONGS_EQUAL(13, LightDriver_GetId(&testDriver));
    STRCMP_EQUAL("testDriver", LightDriver_GetType(&testDriver));
}

TEST(LightDriver, TurnOnCall)
{
    LightDriver_TurnOn(&testDriver);
    LONGS_EQUAL(callCount, 1);
}

TEST(LightDriver, TurnOffCall)
{
    LightDriver_TurnOff(&testDriver);
    LONGS_EQUAL(callCount, 1);
}

TEST(LightDriver, DestroyCall)
{
    LightDriver_Destroy(&testDriver);
    LONGS_EQUAL(callCount, 1);
}

TEST(LightDriver, SetLightCall)
{
    LightDriver_SetLight(&testDriver, 100);
    LONGS_EQUAL(globalLight, 100);
}

int main(int argc, char **argv)
{
    printf("> LightDriverTest ");
    return RUN_ALL_TESTS(argc, argv);
}
