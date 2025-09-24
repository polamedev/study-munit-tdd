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

# add_library(CircularBuffer OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer/CircularBuffer.c)
# target_include_directories(CircularBuffer
# PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer>
# )

# add_library(ClockService OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/ClockService/ClockService.c)
# target_include_directories(ClockService
# PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ClockService>
# )

# add_library(MillisService OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/MillisService/MillisService.c)
# target_include_directories(MillisService
# PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MillisService>
# )
    
# add_library(code-lib 
# STATIC 
# $<TARGET_OBJECTS:CircularBuffer>

# )

# target_link_libraries(code-lib
#     PUBLIC
#     CircularBuffer
#     ClockService
#     MillisService
# )

target_include_directories(code-lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ClockService>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MillisService>
)

target_sources(code-lib
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer/CircularBuffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ClockService/ClockService.c
    ${CMAKE_CURRENT_SOURCE_DIR}/MillisService/MillisService.c
)

add_subdirectory(munit)
add_subdirectory(tests)

add_executable(TDD
    main.c
)

target_link_libraries(TDD
    munit
)