#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "swarming.h"

class TestisBirdInSameNeighbourhood : public ::testing::Test {
protected:
  std::unique_ptr<const sf::Vector2u> boundary;
  std::unique_ptr<const Bird> testBird;
  std::unique_ptr<const Bird> otherBird;

  void SetUp() override {
    const perceptionRadius perception = {
        70.0f,
        70.0f,
        30.0f,
    };

    boundary = std::make_unique<const sf::Vector2u>(50, 50);
    testBird = std::make_unique<const Bird>(1.0f, 1.0f, *boundary, perception);
    otherBird = std::make_unique<const Bird>(1.5f, 1.5f, *boundary, perception);
  }

  void TearDown() override {
    // Code here will be called just after each test in this fixture.
  }
};

TEST_F(TestisBirdInSameNeighbourhood,
       ReturnsTrueWhenBirdIsInTheSameNeighbourhood) {
  // Fixture
  float radius = 3.0f;

  // Test
  bool isInSameNeighbourhood =
      isBirdInSameNeighbourhood(*testBird, *otherBird, radius);

  // Assert
  ASSERT_TRUE(isInSameNeighbourhood);
}

TEST_F(TestisBirdInSameNeighbourhood,
       ReturnsTrueWhenBirdIsNotInTheSameNeighbourhood) {
  // Fixture
  float radius = 0.25f;

  // Test
  bool isInSameNeighbourhood =
      isBirdInSameNeighbourhood(*testBird, *otherBird, radius);

  // Assert
  ASSERT_FALSE(isInSameNeighbourhood);
}

class TestSwarmComputation : public ::testing::Test {
protected:
  std::unique_ptr<const sf::Vector2u> boundary;
  std::unique_ptr<Bird> testBird;
  std::unique_ptr<std::vector<Bird>> otherBirds;

  static constexpr float maxSpeed = 0.1f;
  static constexpr float neighbourhoodRadius = 1.6f;
  static constexpr float weight = 1.0f;

  void SetUp() override {
    const perceptionRadius perception = {
        70.0f,
        70.0f,
        30.0f,
    };

    boundary = std::make_unique<const sf::Vector2u>(50, 50);
    testBird =
        std::make_unique<Bird>(1.0f, 1.0f, *boundary, perception, maxSpeed);
    otherBirds = std::make_unique<std::vector<Bird>>();

    testBird->velocity = sf::Vector2f(0.2f, 0.2f);

    otherBirds->emplace_back(1.5f, 1.5f, *boundary, perception, maxSpeed);
    otherBirds->emplace_back(3.0f, 3.0f, *boundary, perception, maxSpeed);
    otherBirds->emplace_back(1.2f, 1.2f, *boundary, perception, maxSpeed);

    otherBirds->at(0).velocity = sf::Vector2f(0.1f, 0.1f);
    otherBirds->at(1).velocity = sf::Vector2f(1.0f, 1.0f);
    otherBirds->at(2).velocity = sf::Vector2f(0.1f, 0.1f);
  }

  void TearDown() override {
    // Code here will be called just after each test in this fixture.
  }
};

TEST_F(TestSwarmComputation, TestComputeAlignment) {
  // Test
  sf::Vector2f alignment = computeAlignment(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedAlignment = sf::Vector2f(-0.129289329f, -0.129289329f);

  ASSERT_FLOAT_EQ(expectedAlignment.x, alignment.x);
  ASSERT_FLOAT_EQ(expectedAlignment.y, alignment.y);
};

TEST_F(TestSwarmComputation, TestComputeCohesion) {
  // Test
  sf::Vector2f cohesion = computeCohesion(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedCohesion = sf::Vector2f(0.212132037, 0.212132037);

  ASSERT_FLOAT_EQ(expectedCohesion.x, cohesion.x);
  ASSERT_FLOAT_EQ(expectedCohesion.y, cohesion.y);
};

TEST_F(TestSwarmComputation, TestComputeSeparation) {
  // Fixture
  const float separationRadius = neighbourhoodRadius;

  // Test
  sf::Vector2f separation = computeSeparation(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedSeparation = sf::Vector2f(-0.27071068f, -0.27071068f);

  ASSERT_FLOAT_EQ(expectedSeparation.x, separation.x);
  ASSERT_FLOAT_EQ(expectedSeparation.y, separation.y);
};

class TestSwarmComputationWithNoNeighbours : public ::testing::Test {
protected:
  std::unique_ptr<sf::Vector2u> boundary;
  std::unique_ptr<Bird> testBird;
  std::unique_ptr<std::vector<Bird>> otherBirds;

  static constexpr float neighbourhoodRadius = 1.6f;
  static constexpr float weight = 1.0f;
  static constexpr float maxSpeed = 0.1f;

  void SetUp() override {

    const perceptionRadius perception = {
        1.6f,
        1.6f,
        1.6f,
    };

    boundary = std::make_unique<sf::Vector2u>(50, 50);

    testBird =
        std::make_unique<Bird>(1.0f, 1.0f, *boundary, perception, maxSpeed);
    testBird->velocity = sf::Vector2f(1.0f, 1.0f);

    otherBirds = std::make_unique<std::vector<Bird>>();

    otherBirds->emplace_back(20.0f, 20.0f, *boundary, perception, maxSpeed);
    otherBirds->emplace_back(3.0f, 3.0f, *boundary, perception, maxSpeed);
    otherBirds->emplace_back(100.0f, 100.0f, *boundary, perception, maxSpeed);

    otherBirds->at(0).velocity = sf::Vector2f(0.1f, 0.1f);
    otherBirds->at(1).velocity = sf::Vector2f(1.0f, 1.0f);
    otherBirds->at(2).velocity = sf::Vector2f(0.2f, 0.2f);
  }

  void TearDown() override {
    // Code here will be called just after each test in this fixture.
  }
};

TEST_F(TestSwarmComputationWithNoNeighbours,
       TestComputeAlignmentCalculatesZeroWhenNoNeighbours) {
  // Test
  sf::Vector2f alignment = computeAlignment(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedAlignment = sf::Vector2f(0.0f, 0.0f);

  ASSERT_FLOAT_EQ(expectedAlignment.x, alignment.x);
  ASSERT_FLOAT_EQ(expectedAlignment.y, alignment.y);
};

TEST_F(TestSwarmComputationWithNoNeighbours,
       TestComputeCohesionCalculatesZeroWhenNoNeighbours) {
  // Test
  sf::Vector2f cohesion = computeCohesion(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedCohesion = sf::Vector2f(0.0f, 0.0f);

  ASSERT_FLOAT_EQ(expectedCohesion.x, cohesion.x);
  ASSERT_FLOAT_EQ(expectedCohesion.y, cohesion.y);
};

TEST_F(TestSwarmComputationWithNoNeighbours,
       TestComputeSeparationCalculatesZeroWhenNoNeighbours) {
  // Fixture
  const float separationRadius = neighbourhoodRadius;

  // Test
  sf::Vector2f separation = computeSeparation(*testBird, *otherBirds, weight);

  // Assert
  sf::Vector2f expectedSeparation = sf::Vector2f(0.0f, 0.0f);

  ASSERT_FLOAT_EQ(expectedSeparation.x, separation.x);
  ASSERT_FLOAT_EQ(expectedSeparation.y, separation.y);
};
