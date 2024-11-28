set(SOURCES slider.cpp)
add_library(slider ${SOURCES})
target_include_directories(slider PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(slider PUBLIC sfml-system sfml-window sfml-graphics)