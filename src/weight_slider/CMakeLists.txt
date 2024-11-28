set(SOURCES weight_slider.cpp)
add_library(weight_slider ${SOURCES})
target_include_directories(weight_slider PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(weight_slider PUBLIC sfml-system sfml-window sfml-graphics slider)