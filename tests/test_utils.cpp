#include "utils.h"

#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

TEST(TestLimitVector, SpeedIsCappedWhenVectorAboveMaxSpeed) {

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

TEST(TestLimitVector, SpeedIsNotCappedWhenVectorBelowMaxSpeed) {
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

TEST(TestNorm, CalculatesNormCorrectly) {
  // Fixture
  sf::Vector2f vec(3.0f, 4.0f);

  // Test
  float normVal = norm(vec);

  // Assert
  float expectedNorm = 5.0f;
  ASSERT_FLOAT_EQ(expectedNorm, normVal);
}

TEST(TestSetVecMag, CalculatesVectorWithSetMagnitudeCorrectly) { // Fixture
  // Fixture
  sf::Vector2f vec(3.0f, 4.0f);
  float mag = 2.0f;

  // Test
  setVecMag(vec, mag);

  // Assert
  sf::Vector2f expectedMag(1.2f, 1.6f);
  ASSERT_FLOAT_EQ(expectedMag.x, vec.x);
  ASSERT_FLOAT_EQ(expectedMag.y, vec.y);
}

TEST(TestSetVecMag,
     WhenTheProvidedVectorHasNormOfZeroReturnsTheProvidedVector) {
  // Fixture
  sf::Vector2f vec(0.0f, 0.0f);
  float mag = 2.0f;

  // Test
  setVecMag(vec, mag);

  // Assert
  sf::Vector2f expectedVec(0.0f, 0.0f);
  ASSERT_FLOAT_EQ(expectedVec.x, vec.x);
  ASSERT_FLOAT_EQ(expectedVec.y, vec.y);
}