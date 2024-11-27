#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "bird.h"
#include "utils.h"

class TestBird : public ::testing::Test {
protected:
  std::unique_ptr<Bird> testBird;
  std::unique_ptr<const sf::Vector2u> boundary;
  std::unique_ptr<const sf::Vector2f> birdVelocity;

  static constexpr float maxSpeed = 2.0f;

  void SetUp() override {
    birdVelocity = std::make_unique<sf::Vector2f>(1.0f, 1.0f);

    boundary = std::make_unique<sf::Vector2u>(50, 50);
    testBird = std::make_unique<Bird>(1.0f, 1.0f, *boundary, maxSpeed);
    testBird->velocity = *birdVelocity;
  }

  void TearDown() override {}
};

TEST_F(TestBird,
       TestUpdateCalculatesNewVelocityAndPositionCorrectlyWhenBelowMaxSpeed) {
  // Fixture

  const sf::Vector2f acceleration(0.3f, 0.3f);
  const sf::Vector2f birdPosition = testBird->position;

  // Test
  testBird->update(acceleration);

  // Assert
  sf::Vector2f expectedNewVelocity = *birdVelocity + acceleration;
  sf::Vector2f expectedNewPosition = birdPosition + expectedNewVelocity;

  ASSERT_FLOAT_EQ(expectedNewVelocity.x, testBird->velocity.x);
  ASSERT_FLOAT_EQ(expectedNewVelocity.y, testBird->velocity.y);

  ASSERT_FLOAT_EQ(expectedNewPosition.x, testBird->position.x);
  ASSERT_FLOAT_EQ(expectedNewPosition.y, testBird->position.y);
}

TEST_F(TestBird, TestUpdateCapsNewVelocityAtMaxSpeed) {
  // Fixture

  const sf::Vector2f acceleration(0.6f, 0.6f);

  sf::Vector2f expectedNewVelocity = *birdVelocity + acceleration;
  limit_vector(expectedNewVelocity, testBird->maxSpeed);

  sf::Vector2f expectedNewPosition = testBird->position + expectedNewVelocity;

  // Test
  testBird->update(acceleration);

  // Assert
  ASSERT_FLOAT_EQ(expectedNewVelocity.x, testBird->velocity.x);
  ASSERT_FLOAT_EQ(expectedNewVelocity.y, testBird->velocity.y);

  ASSERT_FLOAT_EQ(expectedNewPosition.x, testBird->position.x);
  ASSERT_FLOAT_EQ(expectedNewPosition.y, testBird->position.y);
}