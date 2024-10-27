set(SOURCES bird.cpp)
add_library(bird ${SOURCES})
target_include_directories(bird PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bird PUBLIC sfml-system sfml-window sfml-graphics)
