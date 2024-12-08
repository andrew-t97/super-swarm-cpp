add_subdirectory(utils)
add_subdirectory(bird)
add_subdirectory(swarming)
add_subdirectory(bird_swarm)
add_subdirectory(slider)
add_subdirectory(weight_slider)

add_executable (swarm_demo main.cpp)
target_link_libraries(swarm_demo utils slider weight_slider bird swarming bird_swarm)

add_custom_target(copy_font
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/font ${CMAKE_CURRENT_BINARY_DIR}/font
)
add_dependencies(swarm_demo copy_font)