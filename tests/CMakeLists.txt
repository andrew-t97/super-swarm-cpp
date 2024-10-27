find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(TEST_SOURCES
    test_utils.cpp
    test_bird.cpp
    # Add more test source files here
)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests GTest::gtest_main utils bird)

include(GoogleTest)
gtest_discover_tests(unit_tests)