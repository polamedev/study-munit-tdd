
# Определяем mock в качестве объектной библиотеки
add_library(Mock-MillisService OBJECT mock/MockMillisService.c)
target_include_directories(Mock-MillisService INTERFACE mock)
target_link_libraries(Mock-MillisService PUBLIC MyLib)


add_library(Mock-FormatOutputSpy OBJECT mock/FormatOutputSpy.c)
target_include_directories(Mock-FormatOutputSpy INTERFACE mock)


add_executable(Test-CircularBuffer source/Test-CircularBuffer.c)
target_link_libraries(Test-CircularBuffer munit MyLib Mock-FormatOutputSpy)
add_test(Test-CircularBuffer Test-CircularBuffer)

add_executable(Test-TaskSchedule source/Test-TaskSchedule.c)
target_link_libraries(Test-TaskSchedule munit MyLib Mock-MillisService)
add_test(Test-TaskSchedule Test-TaskSchedule)

add_executable(Test-FormatOutputSpy source/Test-FormatOutputSpy.c)
target_link_libraries(Test-FormatOutputSpy munit Mock-FormatOutputSpy)
add_test(Test-FormatOutputSpy Test-FormatOutputSpy)

add_executable(Test-FormatOutput source/Test-FormatOutput.c)
target_link_libraries(Test-FormatOutput munit MyLib)
add_test(Test-FormatOutput Test-FormatOutput)