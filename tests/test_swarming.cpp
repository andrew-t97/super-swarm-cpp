#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "swarming.h"

class TestisBirdInSameNeighbourhood : public ::testing::Test {
protected:
  std::unique_ptr<const Bird> testBird;
  std::unique_ptr<const Bird> otherBird;

  void SetUp() override {
    testBird = std::make_unique<const Bird>(1.0f, 1.0f);
    otherBird = std::make_unique<const Bird>(1.5f, 1.5f);
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
  std::unique_ptr<const Bird> testBird;
  std::unique_ptr<std::vector<const Bird>> otherBirds;
  const float radius = 1.5f;

  void SetUp() override {
    testBird = std::make_unique<const Bird>(1.0f, 1.0f);
    otherBirds = std::make_unique<std::vector<const Bird>>();

    otherBirds->emplace_back(1.5f, 1.5f);
    otherBirds->emplace_back(2.0f, 2.0f);
    otherBirds->emplace_back(1.2f, 1.2f);
  }

  void TearDown() override {
    // Code here will be called just after each test in this fixture.
  }
};

TEST_F(TestSwarmComputation, TestComputeAlignment) { FAIL(); };
TEST_F(TestSwarmComputation, TestComputeCohesion) { FAIL(); };
TEST_F(TestSwarmComputation, TestComputeSeparation) { FAIL(); };