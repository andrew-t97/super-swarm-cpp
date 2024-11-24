#pragma once
#include <SFML/Graphics.hpp>
#include <type_traits>

float norm(sf::Vector2f vec);

void limit_vector(sf::Vector2f &vec, float limit);

void setVecMag(sf::Vector2f &vec, float mag);