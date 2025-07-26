set(LIBRARY_NAME "libutility")

add_library(${LIBRARY_NAME} ${LIBRARY_NAME}/args.cpp ${LIBRARY_NAME}/config.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIBRARY_NAME} PRIVATE ryml::ryml)

# if(BUILD_TESTING)
#   include(GoogleTest)
#
#   # set(TEST_TARGET "category_test")
#   # add_executable(${TEST_TARGET} ${LIBRARY_NAME}/${TEST_TARGET}.cpp)
#   # target_link_libraries(${TEST_TARGET} PRIVATE ${LIBRARY_NAME} GTest::gtest_main GTest::gmock_main)
#   # gtest_discover_tests(${TEST_TARGET})
#
# endif()
