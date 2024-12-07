#include "weight_slider.h"
#include "utils.h"

BasicSliderWithTitle::BasicSliderWithTitle(const sf::Vector2f &position,
                                           const float width,
                                           const float height,
                                           const sf::Font &font,
                                           const std::string &sliderTitle)
    : Slider(sf::Vector2f(position.x, position.y + slider_offset_from_position),
             width, height - slider_offset_from_position, min_val, max_val,
             font),
      position(position) {

  text.setFont(font);
  text.setCharacterSize(character_size);
  text.setFillColor(sf::Color::White);
  text.setPosition(position);
  text.setString(sliderTitle);
}

void BasicSliderWithTitle::draw(sf::RenderWindow &window) const {
  Slider::draw(window);
  window.draw(text);
}
