# обязательная строка, устанавливает требуемую версию CMake
cmake_minimum_required(VERSION 3.13)

# название проекта, версия, описание в свободной форме
project(
    tdd
    VERSION 1.0
    DESCRIPTION "TDD"
    # языки проекта, если не указать, будет принято, что проект на С и С++
    LANGUAGES C)

# Подключение CTest для тестирования, добавляет определение BUILD_TESTING
include(CTest)

include(cmake/test-file.cmake)

if(BUILD_TESTING)
    add_subdirectory(munit)
    add_subdirectory(tests)
endif()

add_library(code-lib STATIC)

target_include_directories(code-lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/CircularBuffer>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/ClockService>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/MillisService>
)

target_sources(code-lib
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/CircularBuffer/CircularBuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ClockService/ClockService.c
)

add_executable(TDD
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
)

target_link_libraries(TDD
    munit
)