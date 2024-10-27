#include "bird.h"

Bird::Bird(float x, float y) : position(x, y) {
  shape.setPosition(position);
  shape.setRadius(5.0f);
  shape.setFillColor(sf::Color::White);
  shape.setPointCount(3);

  velocity =
      sf::Vector2f((rand() % 100 - 50) / 100.0f, (rand() % 100 - 50) / 100.0f);
}

void Bird::update(const sf::Vector2f &alignment, const sf::Vector2f &cohesion,
                  const sf::Vector2f &separation) {
  velocity += alignment + cohesion + separation;

  float speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
  if (speed > 2.0f) {
    velocity = (velocity / speed) * 2.0f; // Capping the speed at 2.0f
  }

  position += velocity;
  shape.setPosition(position);
}
