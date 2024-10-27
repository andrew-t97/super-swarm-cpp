#pragma once

#include <SFML/Graphics.hpp>

class Bird {

private:
public:
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::CircleShape shape; // Defines a triangle

  Bird(float startPosX, float startPosY);

  void update(const sf::Vector2f &alignment, const sf::Vector2f &cohesion,
              const sf::Vector2f &separation);
};
