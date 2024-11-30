#include "weight_slider.h"
#include "config.h"
#include "utils.h"

#define CHARACTER_SIZE 16
#define SPACE_BETWEEN_TITLE_AND_SLIDER (CHARACTER_SIZE * 0.5)
#define MIN_VAL 0
#define MAX_VAL 100

WeightSlider::WeightSlider(const sf::Vector2f &position, const float width,
                           const float height, const std::string &sliderTitle)
    : position(position),
      slider(position.x,
             position.y + CHARACTER_SIZE + SPACE_BETWEEN_TITLE_AND_SLIDER,
             width, height - CHARACTER_SIZE - SPACE_BETWEEN_TITLE_AND_SLIDER,
             MIN_VAL, MAX_VAL) {

  loadFont(font, std::string(Config::FONT_FILE_NAME));

  text.setFont(font);
  text.setCharacterSize(CHARACTER_SIZE);
  text.setFillColor(sf::Color::White);
  text.setPosition(position);
  text.setString(sliderTitle);
}

void WeightSlider::draw(sf::RenderWindow &window) const {
  slider.draw(window);
  window.draw(text);
}

void WeightSlider::handleEvent(sf::Event &event, sf::RenderWindow &window) {
  slider.handleEvent(event, window);
}

float WeightSlider::getValue() const { return slider.getNormalizedValue(); }
