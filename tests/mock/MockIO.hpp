
#pragma once

#include <MyLib/IO.h>

#include <CppUTest/SimpleString.h>

void MockIO_setup(const SimpleString &mockName, bool strictOrder = false);
void MockIO_teardown();

void MockIO_expectRead(ioAddress add, ioData retData, unsigned int amount = 1);
void MockIO_expectWrite(ioAddress add, ioData writeData, unsigned int amount = 1);

/** МОжно не вызывать если используется плагин */
void MockIO_checkExpectations();
