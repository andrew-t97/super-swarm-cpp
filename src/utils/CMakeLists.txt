set(SOURCES utils.cpp)
add_library(utils ${SOURCES})
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(utils PUBLIC sfml-system sfml-window sfml-graphics)
