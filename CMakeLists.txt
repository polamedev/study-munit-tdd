# обязательная строка, устанавливает требуемую версию CMake
cmake_minimum_required(VERSION 3.13)

# название проекта, версия, описание в свободной форме
project(
    tdd
    VERSION 1.0
    DESCRIPTION "study-munit-TDD"
    # языки проекта, если не указать, будет принято, что проект на С и С++
    LANGUAGES C)

# Подключение CTest для тестирования, добавляет определение BUILD_TESTING
include(CTest)

include(cmake/test-file.cmake)

if(BUILD_TESTING)
    add_subdirectory(munit)
    add_subdirectory(tests)
endif()

add_library(MyLib STATIC)

target_include_directories(MyLib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/MyLib>
)

target_sources(MyLib
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/CircularBuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/TaskSchedule.c
)

add_executable(TDD-example
    ${CMAKE_CURRENT_SOURCE_DIR}/example/main.c
)

target_link_libraries(TDD-example
    munit
)