#pragma once

#include "slider.h"
#include <SFML/Graphics.hpp>

class WeightSlider {
private:
  sf::Vector2f position;
  sf::Text text;
  sf::Font font;
  std::unique_ptr<Slider> slider;

public:
  WeightSlider(const sf::Vector2f &position, const float width,
               const float height, const std::string &sliderTitle);

  void draw(sf::RenderWindow &window) const;
  void handleEvent(sf::Event &event, sf::RenderWindow &window);
  float getValue() const;
};