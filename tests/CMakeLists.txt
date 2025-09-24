add_executable(Tests
    AllTests.c
    CircularBufferTest.c
    ClockServiceTest.c
    MockMillisService.c
)

target_link_libraries(Tests
    munit
    code-lib
)