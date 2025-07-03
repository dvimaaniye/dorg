cmake_minimum_required(VERSION 4.0)

project(dirorg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/UpdateSubmodules.cmake)

if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(libs/libgtest)
endif()

add_subdirectory(libs/libapp)
add_subdirectory(libs/libcategory)
add_subdirectory(libs/liborganizer)

add_subdirectory(app)
