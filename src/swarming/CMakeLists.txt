set(SOURCES swarming.cpp)
add_library(swarming ${SOURCES})
target_include_directories(swarming PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(swarming PUBLIC bird sfml-system sfml-window sfml-graphics)

