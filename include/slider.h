#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Slider {
public:
  Slider(float x, float y, float width, float height, float minValue,
         float maxValue);

  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
  void draw(sf::RenderWindow &window) const;
  float getNormalizedValue() const;

private:
  sf::Vector2f position;
  sf::Vector2f barSize;

  float minValue;
  float maxValue;
  float currentValue;
  float minHandlePositionX;
  float maxHandlePositionX;

  sf::RectangleShape bar;
  sf::CircleShape handle;
  sf::Text valueText;
  sf::Font font;

  bool isMouseDragging = false;

  void handleMousePressed(const sf::Event &event,
                          const sf::RenderWindow &window);
  void handleMouseReleased(const sf::Event &event,
                           const sf::RenderWindow &window);
  void handleMouseMoved(const sf::Event &event, const sf::RenderWindow &window);

  void updateValueText();
};