#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "utils.h"

TEST(TestCapVectorToSpeed, SpeedIsCappedWhenVectorAboveMaxSpeed) {

  // Fixture
  float max_speed = 2.0;
  sf::Vector2f vec(1.0f, 2.0f);

  // Test
  limit_vector(vec, max_speed);

  // Assert
  sf::Vector2f expectedVec(0.89442719f, 1.7888544f);

  ASSERT_FLOAT_EQ(expectedVec.x, vec.x);
  ASSERT_FLOAT_EQ(expectedVec.y, vec.y);
}

TEST(TestCapVectorSpeed, SpeedIsNotCappedWhenVectorBelowMaxSpeed) {
  // Fixture
  float max_speed = 2.0;
  sf::Vector2f vec(1.0f, 1.0f);

  // Test
  limit_vector(vec, max_speed);

  // Assert
  sf::Vector2f expectedVec(1.0f, 1.0f);

  ASSERT_FLOAT_EQ(expectedVec.x, vec.x);
  ASSERT_FLOAT_EQ(expectedVec.y, vec.y);
}