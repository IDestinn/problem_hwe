cmake_minimum_required(VERSION 3.11)
project("problem_hwe" C)
enable_testing()
include(CTest)

set(CMAKE_C_STANDARD 11)

# Library and main application
add_library(sieve_lib STATIC src/sieve.c)
add_executable(sieve_app src/main.c)
target_link_libraries(sieve_app sieve_lib)

# Define test base source and create a special object library for it
set(TEST_BASE_SOURCE tests/test_base.c)
add_library(test_base_obj OBJECT ${TEST_BASE_SOURCE})
target_link_libraries(test_base_obj sieve_lib)

# Find and build test executables, excluding test_base.c
file(GLOB TEST_SOURCES tests/*.c)
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_BASE_SOURCE}")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE} $<TARGET_OBJECTS:test_base_obj>)
    target_link_libraries(${TEST_NAME} sieve_lib)
    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_BINARY_DIR}/tests/${TEST_NAME})
endforeach()