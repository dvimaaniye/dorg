add_executable(app app/main.cpp)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(app libutility liborganizer liblogger)
