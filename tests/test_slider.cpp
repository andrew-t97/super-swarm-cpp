#include "slider.h"

#include <SFML/Graphics.hpp>
#include <format>
#include <gtest/gtest.h>

class TestSliderConstructorValueValidation
    : public ::testing::TestWithParam<std::pair<int, int>> {};

TEST_P(TestSliderConstructorValueValidation,
       WhenMinValueIsGreaterThanMaxValueThenThrowInvalidArgument) {
  // Fixture
  sf::Vector2f pos(0, 0);
  float width = 100;
  float height = 40;
  float minValue = std::get<0>(GetParam());
  float maxValue = std::get<1>(GetParam());

  sf::Font font;

  // Test
  try {
    Slider slider(pos, width, height, minValue, maxValue, font);
  } catch (std::invalid_argument &e) {

    // Assert
    std::string expectedError = std::format(
        "Minimum value {{:.2f}} must be less than the maximum value {{:.2f}}",
        minValue, maxValue);

    ASSERT_STREQ(expectedError.c_str(), e.what());
  }
}

INSTANTIATE_TEST_SUITE_P(TestSlider, TestSliderConstructorValueValidation,
                         ::testing::Values(std::make_pair(10, 5),
                                           std::make_pair(0, 0),
                                           std::make_pair(0, -1)));

class TestSliderValueCaclulation : public ::testing::Test {
protected:
  sf::Vector2f pos;
  sf::Font font;
  float width;
  float height;
  float minValue;
  float maxValue;
  std::unique_ptr<Slider> slider;

  void SetUp() override {
    pos = sf::Vector2f(0, 0);
    width = 100;
    height = 40;
    minValue = 0;
    maxValue = 100;
    slider =
        std::make_unique<Slider>(pos, width, height, minValue, maxValue, font);
  }
};

TEST_F(TestSliderValueCaclulation, CurrentValueIsCalculatedCorrectly) {
  // Fixture

  float handleRadius = height / 2; // 20

  float minHandlePositionX = pos.x;                            // 0
  float maxHandlePositionX = pos.x + width - handleRadius * 2; // 60

  float handleCenterX = 50;

  float expectedCurrentValue =
      minValue + ((handleCenterX - (pos.x + handleRadius)) /
                  (maxHandlePositionX - minHandlePositionX)) *
                     (maxValue - minValue);

  // Assert
  ASSERT_FLOAT_EQ(expectedCurrentValue, slider->getValue());
}

TEST_F(TestSliderValueCaclulation,
       NormalisedCurrentValueIsCalculatedCorrectly) {
  // Fixture

  float expectedNormalisedValue =
      (slider->getValue() - minValue) / (maxValue - minValue);

  // Assert
  ASSERT_FLOAT_EQ(expectedNormalisedValue, slider->getNormalisedValue());
}