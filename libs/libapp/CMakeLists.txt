add_library(libapp libapp/organizer.cpp libapp/args.cpp)

target_include_directories(libapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(libapp PUBLIC libcategory)

if(BUILD_TESTING)
  include(GoogleTest)

  add_executable(mode_test libapp/mode_test.cpp)
  target_link_libraries(mode_test PRIVATE libapp GTest::gtest_main)
  gtest_discover_tests(mode_test)

  add_executable(args_test libapp/args_test.cpp)
  target_link_libraries(args_test PRIVATE libapp GTest::gtest_main)
  gtest_discover_tests(args_test)

endif()
