find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(TEST_SOURCES
    test_utils.cpp
    test_bird.cpp
    test_swarming.cpp
    test_slider.cpp
)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests GTest::gtest_main utils bird swarming slider)

include(GoogleTest)
gtest_discover_tests(unit_tests)