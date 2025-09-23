cmake_minimum_required(VERSION 3.16)

project(mpsim VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

set(SRC_FILES
    moduplay.h
    mpcore.h
    main.c
    core.c
    canvas.c
    input.c
)

list(TRANSFORM SRC_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_executable(mpsim ${SRC_FILES})

target_link_libraries(mpsim PRIVATE SDL3::SDL3)