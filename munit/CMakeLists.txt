add_library(munit STATIC)

target_include_directories(munit
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(munit
    PRIVATE 
    munit.c
)

add_executable(munit-example
    example.c
)

target_link_libraries(munit-example
    munit
)

