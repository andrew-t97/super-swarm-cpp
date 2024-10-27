add_subdirectory(bird)
add_subdirectory(swarming)
add_subdirectory(utils)

add_executable (swarm_demo main.cpp)
target_link_libraries(swarm_demo bird utils swarming)