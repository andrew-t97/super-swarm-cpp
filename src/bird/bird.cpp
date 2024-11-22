#include "bird.h"
#include "utils.h"

Bird::Bird(float x, float y) : position(x, y) {
  shape.setPosition(position);
  shape.setRadius(5.0f);
  shape.setFillColor(sf::Color::White);

  velocity =
      sf::Vector2f((rand() % 100 - 50) / 100.0f, (rand() % 100 - 50) / 100.0f);
}

void Bird::keep_bird_within_boundary(const sf::Vector2u &boundary,
                                     const sf::Vector2f &position,
                                     sf::Vector2f &velocity) {

  sf::Vector2f new_position = position + velocity;
  if (new_position.x > boundary.x || new_position.x < 0) {
    velocity.x = -velocity.x;
  }

  if (new_position.y > boundary.y || new_position.y < 0) {
    velocity.y = -velocity.y;
  }
}

void Bird::update(const sf::Vector2f &alignment, const sf::Vector2f &cohesion,
                  const sf::Vector2f &separation, const float maxSpeed,
                  const sf::Vector2u &boundary) {

  velocity += alignment + cohesion + separation;

  cap_vector_to_max_speed(velocity, maxSpeed);

  keep_bird_within_boundary(boundary, position, velocity);

  position += velocity;

  shape.setPosition(position);
}
