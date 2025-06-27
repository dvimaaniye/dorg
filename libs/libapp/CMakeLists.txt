add_library(libapp libapp/organizer.cpp libapp/args.cpp)

target_include_directories(libapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(libapp PUBLIC libcategory)
