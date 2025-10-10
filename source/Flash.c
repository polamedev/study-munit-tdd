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

#include "Flash.h"

#include <MyLib/IO.h>
#include <MyLib/MicroTime.h>
#include <MyLib/m28w160ect.h>

#define FLASH_WRITE_TIMEOUT_IN_MICROSECONDS 5000

void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

static void resetFlash()
{
    IO_Write(CommandRegister, Reset);
}

static int returnError(int status)
{
    // resetFlash();

    if (status & VppErrorBit)
        return FLASH_VPP_ERROR;
    else if (status & ProgramErrorBit)
        return FLASH_PROGRAM_ERROR;
    else if (status & BlockProtectionErrorBit)
        return FLASH_PROTECTED_BLOCK_ERROR;
    else
        return FLASH_UNKNOWN_PROGRAM_ERROR;
}

int Flash_Write(ioAddress offset, ioData data)
{
    ioData   status    = 0;
    uint32_t timestamp = MicroTime_Get();

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(offset, data);

    status = IO_Read(StatusRegister);
    while ((status & ReadyBit) == 0)
    {
        if (MicroTime_Get() - timestamp >= FLASH_WRITE_TIMEOUT_IN_MICROSECONDS) {
            resetFlash();
            return FLASH_TIMEOUT_ERROR;
        }
        status = IO_Read(StatusRegister);
    }

    resetFlash();

    if (status != ReadyBit) {
        return returnError(status);
    }
    if (data != IO_Read(offset)) {
        return FLASH_READ_BACK_ERROR;
    }

    return FLASH_SUCCESS;
}

FlashStatus Flash_ReadCfi(ioAddress offset, ioData *cfi)
{
    IO_Write(CommandRegister, ReadCfiQuery);

    ioData qry1 = IO_Read(Flash_Cfi_Qry1_Add);
    ioData qry2 = IO_Read(Flash_Cfi_Qry2_Add);
    ioData qry3 = IO_Read(Flash_Cfi_Qry3_Add);

    if (qry1 != Flash_Cfi_Qry1_Data || qry2 != Flash_Cfi_Qry2_Data || qry3 != Flash_Cfi_Qry3_Data) {
        resetFlash();
        return FLASH_ERROR;
    }

    *cfi = IO_Read(offset);

    resetFlash();
    return FLASH_SUCCESS;
}
