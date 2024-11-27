#pragma once

#include <SFML/Graphics.hpp>

#define MAX_BIRD_SPEED 6.0f

typedef struct {
  const float alignmentRadius;
  const float cohesionRadius;
  const float separationRadius;
} perceptionRadius;

class Bird {

public:
  const float maxSpeed;
  const sf::Vector2u boundary;
  const perceptionRadius perception;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::CircleShape shape; // Defines a triangle

  Bird(float startPosX, float startPosY, const sf::Vector2u &boundary,
       const perceptionRadius &perception, float maxSpeed = MAX_BIRD_SPEED);

  /**
   * @brief Updates the bird's position based on separation, cohesion, and
   * alignment
   *
   * This function updates the bird's position, taking into account the provided
   * acceleration steering the bird in a particular
   * direction. The bird's velocity will not exceed its max speed and
   * will keep within its boundary.
   *
   * @param acceleration How much the bird's velocity should change.
   */
  void update(const sf::Vector2f &acceleration);
  void render(sf::RenderWindow &renderWindow);

private:
  /**
   * @brief Adjusts the provided velocity to prevent the position moving outside
   * the boundary
   *
   * This function determines if the provided position will exceed the limits of
   * the provided boundary when the provided velocity is applied to it. For each
   * dimension of the velocity, if the position will exceed the boundary in that
   * dimension when the velocity is applied, then the dimension will be flipped,
   * moving it in the opposite direction. The velocity changes are made
   * in-place.
   */
  void keep_bird_within_boundary();
};
