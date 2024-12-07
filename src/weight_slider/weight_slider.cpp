#include "weight_slider.h"
#include "utils.h"

BasicSliderWithTitle::BasicSliderWithTitle(const sf::Vector2f &pos,
                                           const float width,
                                           const float height,
                                           const sf::Font &font,
                                           const std::string &sliderTitle)
    : Slider(sf::Vector2f(pos.x, pos.y + slider_offset_from_position), width,
             height - slider_offset_from_position, min_val, max_val, font),
      position(pos) {

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
