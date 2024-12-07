#include "bird.h"
#include "utils.h"

#include <random>

Bird::Bird(const sf::Vector2f &position, const sf::Vector2u &boundary,
           const sf::Color &colour, const sf::Vector2f &velocity)
    : position(position), boundary(boundary), velocity(velocity) {

  shape.setRadius(birdRadius);
  shape.setFillColor(colour);
}

void Bird::keep_bird_within_boundary() {

  sf::Vector2f new_position = position + velocity;
  if (new_position.x > boundary.x || new_position.x < 0) {
    velocity.x = -velocity.x;
  }

  if (new_position.y > boundary.y || new_position.y < 0) {
    velocity.y = -velocity.y;
  }
}

void Bird::update(const sf::Vector2f &acceleration) {

  velocity += acceleration;

  limit_vector(velocity, maxSpeed);

  keep_bird_within_boundary();

  position += velocity;

  shape.setPosition(position);
}

void Bird::draw(sf::RenderWindow &window) { window.draw(shape); }