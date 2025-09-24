# обязательная строка, устанавливает требуемую версию CMake
cmake_minimum_required(VERSION 3.13)

# название проекта, версия, описание в свободной форме
project(
    tdd
    VERSION 1.0
    DESCRIPTION "TDD"
    # языки проекта, если не указать, будет принято, что проект на С и С++
    LANGUAGES C)

add_library(code-lib STATIC)

target_include_directories(code-lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ClockService>
)

target_sources(code-lib
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer/CircularBuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ClockService/ClockService.c
)

add_subdirectory(munit)
add_subdirectory(tests)

add_executable(TDD
    main.c
)

target_link_libraries(TDD
    munit
)