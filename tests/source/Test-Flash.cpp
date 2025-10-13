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

#include "FakeMicroTime.h"

#include "MockIO.hpp"

#include <MyLib/Flash.h>
#include <MyLib/IO.h>
#include <MyLib/m28w160ect.h>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTest/TestRegistry.h>
#include <CppUTestExt/MockSupportPlugin.h>

// START: TEST_GROUP2
TEST_GROUP(Flash) {
ioAddress address;
ioData    data;

void setup()
{
    MockIO_setup("ioMock", true);

    address = 0xfeed;
    data    = 0x1dea;
}

void teardown()
{
    MockIO_teardown();

    // При использовании плагина нижнее вызывается автоматически
    // mock().checkExpectations();
    // mock().clear();
}

// START: helpers
void expectCommand(ioData command)
{
    MockIO_expectWrite(CommandRegister, command);
}

void expectWriteData()
{
    MockIO_expectWrite(address, data);
}

void simulateDeviceStatus(ioData status)
{
    MockIO_expectRead(StatusRegister, status);
}

void simulateDeviceStatusWithRepeat(ioData status, int repeatCount)
{
    MockIO_expectRead(StatusRegister, status, repeatCount);
}

void simulateReadback(ioData data)
{
    MockIO_expectRead(address, data);
}

}; // TEST_GROUP(Flash)

TEST(Flash, WriteSucceeds_ReadyImmediately)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit);
    expectCommand(Reset);
    simulateReadback(data);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteSucceeds_NotReadyImmediately)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatusWithRepeat(0, 3);
    simulateDeviceStatus(ReadyBit);
    expectCommand(Reset);
    simulateReadback(data);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_VppError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | VppErrorBit);
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_ProgramError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | ProgramErrorBit);
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_ProtectedBlockError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | BlockProtectionErrorBit);
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROTECTED_BLOCK_ERROR, result);
}

TEST(Flash, WriteFails_FlashUnknownProgramError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit);
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_UNKNOWN_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit);
    expectCommand(Reset);
    simulateReadback(data - 1);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(~ReadyBit);
    simulateDeviceStatus(ReadyBit);
    expectCommand(Reset);
    simulateReadback(data);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_Timeout)
{
    FakeMicroTime_Init(0, 500);
    Flash_Create();
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatusWithRepeat(~ReadyBit, 10);
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

TEST(Flash, WriteFails_TimeoutAtEndOfTime)
{
    FakeMicroTime_Init(0xffffffff, 500);
    Flash_Create();
    expectCommand(ProgramCommand);
    expectWriteData();
    for (int i = 0; i < 10; i++) {
        simulateDeviceStatus(~ReadyBit);
    }
    expectCommand(Reset);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

TEST(Flash, ReadCfi)
{
    MockIO_teardown();
    MockIO_setup("ioMock", true);

    expectCommand(ReadCfiQuery);
    MockIO_expectRead(Flash_Cfi_Qry1_Add, Flash_Cfi_Qry1_Data);
    MockIO_expectRead(Flash_Cfi_Qry2_Add, Flash_Cfi_Qry2_Data);
    MockIO_expectRead(Flash_Cfi_Qry3_Add, Flash_Cfi_Qry3_Data);
    MockIO_expectRead(Flash_Cfi_DeviceCode_Add, Flash_Cfi_DeviceCode_Data);
    expectCommand(Reset);

    ioData      data   = 0;
    FlashStatus result = Flash_ReadCfi(Flash_Cfi_DeviceCode_Add, &data);

    LONGS_EQUAL(result, FLASH_SUCCESS);
    LONGS_EQUAL(data, Flash_Cfi_DeviceCode_Data);
}

TEST(Flash, ErrorCfi)
{
    MockIO_teardown();
    MockIO_setup("ioMock", true);

    expectCommand(ReadCfiQuery);
    MockIO_expectRead(Flash_Cfi_Qry1_Add, 1);
    MockIO_expectRead(Flash_Cfi_Qry2_Add, 2);
    MockIO_expectRead(Flash_Cfi_Qry3_Add, 3);
    expectCommand(Reset);

    ioData      data   = 0;
    FlashStatus result = Flash_ReadCfi(Flash_Cfi_DeviceCode_Add, &data);

    LONGS_EQUAL(result, FLASH_ERROR);
}

TEST(Flash, EraseSucceeds_ReadyImmediately)
{

    ioAddress eraseBlock = 0x30;
    expectCommand(EraseCommand);
    MockIO_expectWrite(eraseBlock, EraseAddressConfirm);
    simulateDeviceStatus(ReadyBit);

    int result = Flash_Erase(eraseBlock);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

int main(int argc, char **argv)
{
    MockSupportPlugin mockPlugin;

    // Подключаем плагин mockSupport
    // Что позволит не вызывать mock().clear(); и mock().checkExpectations
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return RUN_ALL_TESTS(argc, argv);
}
