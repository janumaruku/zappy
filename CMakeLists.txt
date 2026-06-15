cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(zappy VERSION 1.0 LANGUAGES CXX)

add_library(warning_options INTERFACE)

target_compile_options(warning_options INTERFACE -Wall -Wextra -Werror)

add_subdirectory(src)

add_subdirectory(libs)

enable_testing()

add_subdirectory(tests)
