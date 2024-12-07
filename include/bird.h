#pragma once

#include <SFML/Graphics.hpp>

class Bird {

public:
  const sf::Vector2u boundary;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::CircleShape shape;

  static constexpr float maxSpeed = 6.0f;
  static constexpr float birdRadius = 5.0f;

  /**
   * @brief Constructs a new Bird object
   *
   * @param startPos The starting position of the bird.
   * @param boundary The boundary of the bird's movement.
   * @param colour The colour of the bird.
   * @param velocity The starting velocity of the bird.
   * @return A new Bird object
   */
  Bird(const sf::Vector2f &startPos, const sf::Vector2u &boundary,
       const sf::Color &colour, const sf::Vector2f &velocity);

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

  /**
   * @brief Draws the bird in the provided render window
   *
   * @param renderWindow The window to draw the bird in
   */
  void draw(sf::RenderWindow &renderWindow);

private:
  /**
   * @brief Adjusts the provided velocity to prevent the bird moving outside
   * its boundary
   *
   * This function determines if the bird's position will exceed the limits of
   * its boundary when its current velocity is applied to it. For each
   * dimension of the velocity, if the position will exceed the boundary in that
   * dimension when the velocity is applied, then the velocity's dimension will
   * be flipped, moving it in the opposite direction. The velocity changes are
   * made in-place.
   */
  void keep_bird_within_boundary();
};
