#pragma once
#include <SFML/Graphics.hpp>
#include <type_traits>

float norm(sf::Vector2f vec);

void cap_vector_to_max_speed(sf::Vector2f &vec, float maxSpeed);