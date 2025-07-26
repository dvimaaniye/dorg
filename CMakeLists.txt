cmake_minimum_required(VERSION 3.31)

project(dirorg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Boost Configuration ---
find_package(Boost 1.83 CONFIG REQUIRED)
if(Boost_FOUND)
	message(STATUS "Boost found at: ${Boost_INCLUDE_DIRS}")
	include_directories(${Boost_INCLUDE_DIRS})
else()
	message(FATAL_ERROR "Boost not found. Please install the boost development packages.")
endif()
# --- End Boost Configuration ---

include(cmake/UpdateSubmodules.cmake)

if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(external/gtest EXCLUDE_FROM_ALL)
endif()

add_subdirectory(external/ryml)

add_subdirectory(libs/libutility)
add_subdirectory(libs/liborganizer)
add_subdirectory(libs/liblogger)

add_subdirectory(app)
