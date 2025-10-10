
#pragma once

#include <MyLib/IO.h>

#include <CppUTest/SimpleString.h>

void MockIO_setMockName(const SimpleString &mockName);
void MockIO_resetMockName();

void MockIO_expectRead(ioAddress add, ioData retData, unsigned int amount = 1);
void MockIO_expectWrite(ioAddress add, ioData writeData, unsigned int amount = 1);
void MockIO_checkExpectations();
