
# Определяем mock в качестве объектной библиотеки
add_library(Mock-MillisService OBJECT mock/StubMillisService.c)
target_include_directories(Mock-MillisService INTERFACE mock)
target_link_libraries(Mock-MillisService PUBLIC MyLib)

# Объектная библиотека мока модуля MyLib/IO с использованием CppUTest
add_library(Mock-MockIO OBJECT mock/MockIO.cpp)
target_include_directories(Mock-MockIO INTERFACE mock)
target_link_libraries(Mock-MockIO PUBLIC MyLib CppUTest::CppUTestExt)

# Объектная библиотека фейка microtime
add_library(Mock-FakeMicroTime OBJECT mock/FakeMicroTime.c)
target_include_directories(Mock-FakeMicroTime INTERFACE mock)
target_link_libraries(Mock-FakeMicroTime PUBLIC MyLib)



add_library(Mock-SpyFormatOutput OBJECT mock/SpyFormatOutput.c)
target_include_directories(Mock-SpyFormatOutput INTERFACE mock)


add_executable(Test-CircularBuffer source/Test-CircularBuffer.c)
target_link_libraries(Test-CircularBuffer munit MyLib Mock-SpyFormatOutput)
add_test(Test-CircularBuffer Test-CircularBuffer)

add_executable(Test-TaskSchedule source/Test-TaskSchedule.c)
target_link_libraries(Test-TaskSchedule munit MyLib Mock-MillisService)
add_test(Test-TaskSchedule Test-TaskSchedule)

add_executable(Test-SpyFormatOutput source/Test-SpyFormatOutput.c)
target_link_libraries(Test-SpyFormatOutput munit Mock-SpyFormatOutput)
add_test(Test-SpyFormatOutput Test-SpyFormatOutput)

add_executable(Test-FormatOutput source/Test-FormatOutput.c)
target_link_libraries(Test-FormatOutput munit MyLib)
add_test(Test-FormatOutput Test-FormatOutput)

add_executable(Test-MockIO source/Test-MockIO.cpp)
target_link_libraries(Test-MockIO MyLib Mock-MockIO CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(Test-MockIO Test-MockIO)

add_executable(Test-FakeMicroTime source/Test-FakeMicroTime.cpp)
target_link_libraries(Test-FakeMicroTime MyLib Mock-FakeMicroTime CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(Test-FakeMicroTime Test-FakeMicroTime)

add_executable(Test-Flash source/Test-Flash.cpp)
target_link_libraries(Test-Flash MyLib Mock-FakeMicroTime Mock-MockIO CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(Test-Flash Test-Flash)

add_executable(Test-Thread source/Test-Thread.cpp)
target_link_libraries(Test-Thread CppUTest::CppUTest CppUTest::CppUTestExt MyLib)
add_test(Test-Thread Test-Thread)
