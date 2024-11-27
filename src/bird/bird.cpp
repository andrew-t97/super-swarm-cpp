#include "bird.h"
#include "utils.h"

#include <random>

Bird::Bird(float x, float y, const sf::Vector2u &boundary,
           const perceptionRadius &perception, float maxSpeed)
    : position(x, y), maxSpeed(maxSpeed), boundary(boundary),
      perception(perception) {

  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed generator
  std::uniform_int_distribution<> colorDistr(0, 255);
  std::uniform_real_distribution<> velocityDistr(-100.0f, 100.0f);

  shape.setPosition(position);
  shape.setRadius(5.0f);

  shape.setFillColor(
      sf::Color(colorDistr(gen), colorDistr(gen), colorDistr(gen)));

  velocity = sf::Vector2f(velocityDistr(gen), velocityDistr(gen));
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

void Bird::render(sf::RenderWindow &window) { window.draw(shape); }