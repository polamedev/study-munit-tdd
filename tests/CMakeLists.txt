add_executable(Tests
    AllTests.c
    CircularBufferTest.c
    ClockServiceTest.c
)

target_link_libraries(Tests
    munit
    code-lib
)