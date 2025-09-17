# обязательная строка, устанавливает требуемую версию CMake
cmake_minimum_required(VERSION 3.13)

# название проекта, версия, описание в свободной форме
project(
    tdd
    VERSION 1.0
    DESCRIPTION "TDD"
    # языки проекта, если не указать, будет принято, что проект на С и С++
    LANGUAGES C)

add_subdirectory(munit)

add_executable(TDD
    main.c
)

target_link_libraries(TDD
    munit
)