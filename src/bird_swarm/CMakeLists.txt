set(SOURCES bird_swarm.cpp)
add_library(bird_swarm ${SOURCES})
target_include_directories(bird_swarm PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bird_swarm PUBLIC sfml-system sfml-window sfml-graphics bird swarming)