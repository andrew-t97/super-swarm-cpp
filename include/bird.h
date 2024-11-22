#pragma once

#include <SFML/Graphics.hpp>

class Bird {

public:
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::CircleShape shape; // Defines a triangle

  Bird(float startPosX, float startPosY);

  /**
   * @brief Updates the bird's position based on separation, cohesion, and
   * alignment
   *
   * This function updates the bird's position, taking into account the provided
   * separation, cohesion, and alignment, steering the bird in a particular
   * direction. The bird's velocity (which is adjusted by the alignment,
   * cohesion, and alignment) will not exceed the provided max speed and will
   * keep within the provided boundary.
   *
   * @param alignment The vector the bird should head towards based on the
   * direction of other nearby birds.
   * @param cohesion The vector the bird should head towards to stay close to
   * other birds.
   * @param separation The vector the bird should head towards to not get too
   * close to other birds.
   * @param maxSpeed The maximum speed the bird is allowed to travel.
   * @param boundary The boundary the bird must stay within.
   */
  void
  update(const sf::Vector2f &alignment, const sf::Vector2f &cohesion,
         const sf::Vector2f &separation, const float maxSpeed,
         const sf::Vector2u &boundary); // TODO: Remove boundary and maxSpeed.

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
   *
   * @param boundary The boundary we're checking the position and velocity
   * against.
   * @param position The position we wish to apply the velocity to.
   * @param velocity The velocity we wish to apply to the provided position
   */
  void keep_bird_within_boundary(const sf::Vector2u &boundary,
                                 const sf::Vector2f &position,
                                 sf::Vector2f &velocity);
};
