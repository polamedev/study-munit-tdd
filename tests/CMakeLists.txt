
# Определяем mock в качестве объектной библиотеки
add_library(Mock-MillisService OBJECT source/MockMillisService.c)
target_link_libraries(Mock-MillisService PRIVATE code-lib)


add_executable(Test-CircularBuffer source/CircularBufferTest.c)
target_link_libraries(Test-CircularBuffer munit code-lib)
add_test(Test-CircularBuffer Test-CircularBuffer)

add_executable(Test-TaskScheduleTest source/TaskScheduleTest.c $<TARGET_OBJECTS:Mock-MillisService>)
target_link_libraries(Test-TaskScheduleTest munit code-lib)
add_test(Test-TaskScheduleTest Test-TaskScheduleTest)
