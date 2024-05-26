cmake_minimum_required(VERSION 3.28)
project(data_structure_with_c C)

set(CMAKE_C_STANDARD 11)

enable_testing()

include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)