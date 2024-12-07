#pragma once

#include "slider.h"
#include <SFML/Graphics.hpp>

/**
 *  An extension of the Slider class which manages and renders title text for
 * the slider
 */
class BasicSliderWithTitle : public Slider {
public:
  /**
   * @brief creates a new instance of the BasicSliderWithTitle class
   *
   * @param pos The position of the slider
   * @param width The width of the slider
   * @param height The height of the slider
   * @param font The font to use for the slider's value text
   * @param sliderTitle The title to display above the slider.
   */
  BasicSliderWithTitle(const sf::Vector2f &pos, const float width,
                       const float height, const sf::Font &font,
                       const std::string &sliderTitle);

  /**
   * @brief Draws the slider and its title text.
   *
   * @param window The window to draw the slider and title text to.
   */
  void draw(sf::RenderWindow &window) const;

private:
  sf::Vector2f position;
  sf::Text text;
  sf::Font font;

  static constexpr int character_size = 16;
  static constexpr float space_between_title_and_slider = character_size * 0.5f;
  static constexpr float slider_offset_from_position =
      character_size + space_between_title_and_slider;
  static constexpr float min_val = 0.0f;
  static constexpr float max_val = 100.0f;
};