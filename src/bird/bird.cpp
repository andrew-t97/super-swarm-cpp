#include "bird.h"
#include "utils.h"

#include <random>

Bird::Bird(const sf::Vector2f &position, const sf::Vector2u &boundary,
           const perceptionRadius &perception, float maxSpeed)
    : position(position), maxSpeed(maxSpeed), boundary(boundary),
      perception(perception) {

  // TODO: Move this to main and add a velocity parameter.
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed generator

  std::uniform_int_distribution<> colourDistr(minBirdColour, maxBirdColour);
  std::uniform_real_distribution<> velocityDistr(-MAX_BIRD_SPEED,
                                                 MAX_BIRD_SPEED);

  shape.setRadius(birdRadius);
  shape.setFillColor(
      sf::Color(colourDistr(gen), colourDistr(gen),
                colourDistr(gen))); // Randomly setting the birds colour

  velocity =
      sf::Vector2f(velocityDistr(gen), velocityDistr(gen)); // Random velocity
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