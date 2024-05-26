cmake_minimum_required(VERSION 3.28)
project(data_structure_with_c C)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)
include_directories(tests/include)
add_subdirectory(src)
add_subdirectory(tests)