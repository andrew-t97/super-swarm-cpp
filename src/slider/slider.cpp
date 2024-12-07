#include "slider.h"
#include "utils.h"

#include <format>

Slider::Slider(const sf::Vector2f &pos, const float width, const float height,
               const float minValue, const float maxValue, const sf::Font &font)
    : position(pos), barSize(width, height), minValue(minValue),
      maxValue(maxValue), font(font) {

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

  minHandlePositionX = position.x;
  maxHandlePositionX = position.x + barSize.x - handle.getRadius() * 2;

  initialiseValueText();

  setHandleXPosition(position.x + (width / 2) - handle.getRadius());

  update();
}

void Slider::initialiseValueText() {

  float spaceWidthFromEndOfBar = barSize.x * bar_to_text_space_ratio;

  // Places the text at the end of the bar with a little bit of space
  float valueTextPositionX =
      bar.getPosition().x + barSize.x + spaceWidthFromEndOfBar;

  // Centers the text vertically with the bar
  float valueTextPositionY = bar.getPosition().y + (barSize.y / 2) -
                             (valueText.getCharacterSize() / 3);

  valueText.setFont(font);
  valueText.setCharacterSize(character_size);
  valueText.setFillColor(sf::Color::White);
  valueText.setPosition(valueTextPositionX, valueTextPositionY);
}

void Slider::handleMousePressed(const sf::Event &event,
                                const sf::RenderWindow &window) {
  if (event.mouseButton.button == sf::Mouse::Left) {

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    isMouseDragging = handle.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
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

  setHandleXPosition(newX);

  update();
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

float Slider::getValue() const noexcept { return currentValue; }

void Slider::setHandleXPosition(float x) {
  // Constrain handle position
  if (x < minHandlePositionX)
    x = minHandlePositionX;
  if (x > maxHandlePositionX)
    x = maxHandlePositionX;

  handle.setPosition(x, position.y);
}

void Slider::updateCurrentValue() {
  float handleCenterX = handle.getPosition().x + handle.getRadius();

  // Calculates the current value based on the current position of the handle
  // and its range of possible positions
  currentValue =
      minValue + ((handleCenterX - (position.x + handle.getRadius())) /
                  (maxHandlePositionX - minHandlePositionX)) *
                     (maxValue - minValue);
}

void Slider::updateValueText() {
  std::string text = std::format("{:.2f}", getNormalizedValue());
  valueText.setString(text);
}

void Slider::update() {
  updateCurrentValue();
  updateValueText();
}