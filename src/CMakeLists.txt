add_subdirectory(bird)
add_subdirectory(swarming)
add_subdirectory(utils)
add_subdirectory(bird_swarm)

add_executable (swarm_demo main.cpp)
target_link_libraries(swarm_demo bird utils swarming bird_swarm)