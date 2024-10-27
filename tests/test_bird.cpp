#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "bird.h"
#include "utils.h"

TEST(TestBird,
     TestUpdateCalculatesNewVelocityAndPositionCorrectlyWhenBelowMaxSpeed) {
  // Fixture
  Bird testBird(1.0f, 1.0f);
  testBird.velocity = sf::Vector2f(1.0f, 1.0f);

  const sf::Vector2f alignment(0.1f, 0.1f);
  const sf::Vector2f cohesion(0.1f, 0.1f);
  const sf::Vector2f separation(0.1f, 0.1f);

  const float maxSpeed = 2.0f;

  // Test
  testBird.update(alignment, cohesion, separation, maxSpeed);

  // Assert
  sf::Vector2f expectedNewVelocity(1.3f, 1.3f);
  sf::Vector2f expectedNewPosition(2.3f, 2.3f);

  ASSERT_FLOAT_EQ(expectedNewVelocity.x, testBird.velocity.x);
  ASSERT_FLOAT_EQ(expectedNewVelocity.y, testBird.velocity.y);

  ASSERT_FLOAT_EQ(expectedNewPosition.x, testBird.position.x);
  ASSERT_FLOAT_EQ(expectedNewPosition.y, testBird.position.y);
}

TEST(TestBird, TestUpdateCapsNewVelocityAtMaxSpeed) {
  // Fixture
  Bird testBird(1.0f, 1.0f);
  testBird.velocity = sf::Vector2f(1.0f, 1.0f);

  const sf::Vector2f alignment(0.2f, 0.2f);
  const sf::Vector2f cohesion(0.2f, 0.2f);
  const sf::Vector2f separation(0.2f, 0.2f);

  const float maxSpeed = 2.0f;

  sf::Vector2f expectedNewVelocity =
      testBird.velocity + alignment + cohesion + separation;
  cap_vector_to_max_speed(expectedNewVelocity, maxSpeed);

  sf::Vector2f expectedNewPosition = testBird.position + expectedNewVelocity;

  // Test
  testBird.update(alignment, cohesion, separation, maxSpeed);

  // Assert
  ASSERT_FLOAT_EQ(expectedNewVelocity.x, testBird.velocity.x);
  ASSERT_FLOAT_EQ(expectedNewVelocity.y, testBird.velocity.y);

  ASSERT_FLOAT_EQ(expectedNewPosition.x, testBird.position.x);
  ASSERT_FLOAT_EQ(expectedNewPosition.y, testBird.position.y);
}