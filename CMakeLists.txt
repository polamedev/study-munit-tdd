# обязательная строка, устанавливает требуемую версию CMake
cmake_minimum_required(VERSION 3.13)

# название проекта, версия, описание в свободной форме
project(
    tdd
    VERSION 1.0
    DESCRIPTION "study-munit-TDD"
    # языки проекта, если не указать, будет принято, что проект на С и С++
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(CppUTest REQUIRED)

# Кажется не нужно, при выборе дебажной сборки добавляется флаг -g, его пока достаточно
# add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>")
add_compile_options("-Wall;-Wextra;-pedantic")
# add_compile_options("-O3;-lto")
# add_compile_options("-v")

add_compile_definitions("$<$<CONFIG:DEBUG>:-DMUNIT_NO_FORK>")

# Подключение CTest для тестирования, добавляет определение BUILD_TESTING
include(CTest)

include(cmake/test-file.cmake)

if(BUILD_TESTING)
    add_subdirectory(munit)
    add_subdirectory(tests)
endif()

add_library(MyLib STATIC)

target_include_directories(MyLib
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/MyLib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(MyLib
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/CircularBuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/TaskSchedule.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/FormatOutput.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Flash.c
)

add_executable(TDD-example
    ${CMAKE_CURRENT_SOURCE_DIR}/example/main.c
)

target_link_libraries(TDD-example
    munit
)