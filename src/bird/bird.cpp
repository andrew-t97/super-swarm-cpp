#include "bird.h"
#include "utils.h"

Bird::Bird(float x, float y) : position(x, y) {
  shape.setPosition(position);
  shape.setRadius(5.0f);
  shape.setFillColor(sf::Color::White);

  velocity =
      sf::Vector2f((rand() % 100 - 50) / 100.0f, (rand() % 100 - 50) / 100.0f);
}

void Bird::update(const sf::Vector2f &alignment, const sf::Vector2f &cohesion,
                  const sf::Vector2f &separation, const float maxSpeed) {
  velocity += alignment + cohesion + separation;

  cap_vector_to_max_speed(velocity, maxSpeed);

  position += velocity;
  shape.setPosition(position);
}
