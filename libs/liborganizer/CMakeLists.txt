set(LIBRARY_NAME "liborganizer")
add_library(${LIBRARY_NAME} ${LIBRARY_NAME}/organizer.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PUBLIC libutility)

if(BUILD_TESTING)
  include(GoogleTest)
  set(TEST_TARGET "organizer_test")

  add_executable(${TEST_TARGET} ${LIBRARY_NAME}/${TEST_TARGET}.cpp)
  target_link_libraries(${TEST_TARGET} PRIVATE ${LIBRARY_NAME}
                                               GTest::gtest_main)
  gtest_discover_tests(${TEST_TARGET})

endif()
