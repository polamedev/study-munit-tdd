add_executable(Tests
    AllTests.c
    CircularBufferTest.c
)

target_link_libraries(Tests
    munit
    CircularBuffer
)