add_subdirectory(utils)
add_subdirectory(bird)
add_subdirectory(swarming)
add_subdirectory(bird_swarm)
add_subdirectory(slider)
add_subdirectory(weight_slider)

add_executable (swarm_demo main.cpp)
target_link_libraries(swarm_demo utils slider weight_slider bird swarming bird_swarm)

# Post-build command
add_custom_command(
    TARGET swarm_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/font/arial.ttf
            $<TARGET_FILE_DIR:swarm_demo>
)