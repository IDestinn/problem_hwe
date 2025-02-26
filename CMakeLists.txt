cmake_minimum_required(VERSION 3.11)
project("problem_hwe" C)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_library(sieve_lib STATIC src/sieve.c)
add_executable(sieve_app src/main.c)
target_link_libraries(sieve_app sieve_lib)

add_executable(test_sieve tests/test.c)
target_link_libraries(test_sieve sieve_lib)

add_test(NAME test_sieve COMMAND test_sieve)