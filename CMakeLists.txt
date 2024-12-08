cmake_minimum_required(VERSION 3.10)
project(SwarmDemo)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)

# Install the executable
install(TARGETS swarm_demo
    RUNTIME DESTINATION bin)

# Install the fonts
install(DIRECTORY font/
    DESTINATION bin/font
    FILES_MATCHING PATTERN "*.ttf")
