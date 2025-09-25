
# Определяем mock в качестве объектной библиотеки
add_library(Mock-MillisService OBJECT source/MockMillisService.c)
target_link_libraries(Mock-MillisService PRIVATE code-lib)


add_executable(Test-CircularBuffer source/CircularBufferTest.c)
target_link_libraries(Test-CircularBuffer munit code-lib)
add_test(Test-CircularBuffer Test-CircularBuffer)

add_executable(Test-ClockServiceTest source/ClockServiceTest.c $<TARGET_OBJECTS:Mock-MillisService>)
target_link_libraries(Test-ClockServiceTest munit code-lib)
add_test(Test-ClockServiceTest Test-ClockServiceTest)
