
# Определяем mock в качестве объектной библиотеки
add_library(Mock-MillisService OBJECT mocks/MockMillisService.c)
target_include_directories(Mock-MillisService INTERFACE mocks)
target_link_libraries(Mock-MillisService PUBLIC code-lib)


add_library(Mock-FormatOutputSpy OBJECT mocks/FormatOutputSpy.c)
target_include_directories(Mock-FormatOutputSpy INTERFACE mocks)


add_executable(Test-CircularBuffer source/CircularBufferTest.c)
target_link_libraries(Test-CircularBuffer munit code-lib)
add_test(Test-CircularBuffer Test-CircularBuffer)

add_executable(Test-TaskScheduleTest source/TaskScheduleTest.c)
target_link_libraries(Test-TaskScheduleTest munit code-lib Mock-MillisService)
add_test(Test-TaskScheduleTest Test-TaskScheduleTest)

add_executable(Test-FormatOutputSpy source/FormatOutputSpyTest.c)
target_link_libraries(Test-FormatOutputSpy munit Mock-FormatOutputSpy)
add_test(Test-FormatOutputSpy Test-FormatOutputSpy)
