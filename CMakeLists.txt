cmake_minimum_required(VERSION 4.0)

project(dirorg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/libcategory)
add_subdirectory(libs/libapp)

add_subdirectory(app)
