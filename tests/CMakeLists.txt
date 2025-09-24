
add_library(mock STATIC MockMillisService.c)
target_link_libraries(mock 
    PRIVATE
    code-lib
)



add_executable(Tests
    AllTests.c
    CircularBufferTest.c
    ClockServiceTest.c
)

target_link_libraries(Tests
    munit
    # mock должен идти перед code-lib для подмены реализации
    mock 
    code-lib
)