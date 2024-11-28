#include "slider.h"
#include "config.h"
#include "utils.h"

#include <format>

#define CHARACTER_SIZE 16
#define BAR_TO_TEXT_SPACE_RATIO 0.05

Slider::Slider(float x, float y, float width, float height, float minValue,
               float maxValue)
    : position(x, y), barSize(width, height), minValue(minValue),
      maxValue(maxValue), currentValue(maxValue / 2) {

  if (minValue >= maxValue) {
    throw std::invalid_argument(
        std::format("Minimum value {{:.2f}} must be less than the maximum "
                    "value {{:.2f}}",
                    minValue, maxValue));
  }

  bar.setPosition(position);
  bar.setSize(barSize);
  bar.setFillColor(sf::Color::White);

  handle.setRadius(barSize.y / 2);
  handle.setFillColor(sf::Color::Blue);
  handle.setPosition(x + (width / 2), y);

  // The handle circle doesn't exceed the x boundaries of the bar
  minHandlePositionX = position.x;
  maxHandlePositionX = position.x + barSize.x - handle.getRadius() * 2;

  loadFont(font, std::string(Config::FONT_FILE_NAME));

  float spaceWidthFromEndOfBar = barSize.x * BAR_TO_TEXT_SPACE_RATIO;

  // Places the text at the end of the bar with a little bit of space
  float valueTextPositionX =
      bar.getPosition().x + barSize.x + spaceWidthFromEndOfBar;

  // Centres the text vertically with the bar
  float valueTextPositionY = bar.getPosition().y + (barSize.y / 2) -
                             (valueText.getCharacterSize() / 3);

  valueText.setFont(font);
  valueText.setCharacterSize(CHARACTER_SIZE);
  valueText.setFillColor(sf::Color::White);
  valueText.setPosition(valueTextPositionX, valueTextPositionY);

  updateValueText();
}

void Slider::handleMousePressed(const sf::Event &event,
                                const sf::RenderWindow &window) {
  if (event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (handle.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                          static_cast<float>(mousePos.y))) {
      isMouseDragging = true;
    }
  }
}

void Slider::handleMouseReleased(const sf::Event &event,
                                 const sf::RenderWindow &window) {
  if (event.mouseButton.button == sf::Mouse::Left) {
    isMouseDragging = false;
  }
}

void Slider::handleMouseMoved(const sf::Event &event,
                              const sf::RenderWindow &window) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  float newX = static_cast<float>(mousePos.x) - handle.getRadius();

  // Constrain handle position
  if (newX < minHandlePositionX)
    newX = minHandlePositionX;
  if (newX > maxHandlePositionX)
    newX = maxHandlePositionX;

  handle.setPosition(newX, handle.getPosition().y);

  float handleCenterX = handle.getPosition().x + handle.getRadius();

  // Calculates the current value based on the current position of the handle
  // and its range of possible positions
  currentValue =
      minValue + (handleCenterX - (position.x + handle.getRadius())) /
                     (maxHandlePositionX - minHandlePositionX) *
                     (maxValue - minValue);

  updateValueText();
}

void Slider::handleEvent(const sf::Event &event,
                         const sf::RenderWindow &window) {

  if (event.type == sf::Event::MouseButtonPressed) {
    handleMousePressed(event, window);
  } else if (event.type == sf::Event::MouseButtonReleased) {
    handleMouseReleased(event, window);
  } else if (event.type == sf::Event::MouseMoved && isMouseDragging) {
    handleMouseMoved(event, window);
  }
}

void Slider::draw(sf::RenderWindow &window) const {
  window.draw(bar);
  window.draw(handle);
  window.draw(valueText);
}

float Slider::getNormalizedValue() const {
  return (currentValue - minValue) / (maxValue - minValue);
}

void Slider::updateValueText() {
  std::string text = std::format("{:.2f}", getNormalizedValue());
  valueText.setString(text);
}