set(LIBRARY_NAME "libcategory")
add_library(${LIBRARY_NAME} ${LIBRARY_NAME}/category.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTING)
  include(GoogleTest)
  set(TEST_TARGET "category_test")

  add_executable(${TEST_TARGET} ${LIBRARY_NAME}/${TEST_TARGET}.cpp)
  target_link_libraries(${TEST_TARGET} PRIVATE ${LIBRARY_NAME}
                                               GTest::gtest_main)
  gtest_discover_tests(${TEST_TARGET})

endif()
