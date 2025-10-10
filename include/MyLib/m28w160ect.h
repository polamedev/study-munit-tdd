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

typedef enum {
    CommandRegister = 0x0,
    StatusRegister  = 0x0
} Flash_Registers;

typedef enum {
    ProgramCommand = 0x40,
    ReadCfiQuery   = 0x98, // Запрос на чтение cfi
    Reset          = 0xff
} Flash_Command;

typedef enum {
    ReadyBit                = 1 << 7,
    EraseSuspendBit         = 1 << 6,
    EraseErrorBit           = 1 << 5,
    ProgramErrorBit         = 1 << 4,
    VppErrorBit             = 1 << 3,
    ProgramSuspendBit       = 1 << 2,
    BlockProtectionErrorBit = 1 << 1,
    ReservedBit             = 1
} StatusRegisterBits;

typedef enum {
    Flash_Cfi_ManufacturerCode_Address = 0x00,
    Flash_Cfi_ManufacturerCode_Data    = 0x0020,

    Flash_Cfi_Qry1_Add  = 0x10,
    Flash_Cfi_Qry1_Data = 0x51,

} Flash_Cfi;

