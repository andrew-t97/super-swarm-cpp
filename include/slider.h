#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// TODO: Add dosctrings
// TODO: Add tests

class Slider {
public:
  Slider(const sf::Vector2f &pos, const float width, const float height,
         const float minValue, const float maxValue);

  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);

  void draw(sf::RenderWindow &window) const;

  float getValue() const;

  float getNormalizedValue() const;

private:
  static constexpr int character_size = 16;
  static constexpr float bar_to_text_space_ratio = 0.05f;

  sf::Vector2f position = sf::Vector2f(0, 0);
  sf::Vector2f barSize = sf::Vector2f(100, 40);

  float minValue = 0.0f;
  float maxValue = 100.0f;
  float currentValue = 50.0f;
  float minHandlePositionX;
  float maxHandlePositionX;

  sf::RectangleShape bar;
  sf::CircleShape handle;
  sf::Text valueText;
  sf::Font font;

  bool isMouseDragging = false;

  void initialiseValueText();

  void handleMousePressed(const sf::Event &event,
                          const sf::RenderWindow &window);
  void handleMouseReleased(const sf::Event &event,
                           const sf::RenderWindow &window);
  void handleMouseMoved(const sf::Event &event, const sf::RenderWindow &window);

  void updateCurrentValue();

  void updateValueText();

  void update();

  void setHandleXPosition(float x);
};
