
add_library(mock STATIC source/MockMillisService.c)
target_link_libraries(mock 
    PRIVATE
    code-lib
)



add_executable(Tests
    source/AllTests.c
    source/CircularBufferTest.c
    source/ClockServiceTest.c
)

target_link_libraries(Tests
    munit
    # mock должен идти перед code-lib для подмены реализации
    mock 
    code-lib
)