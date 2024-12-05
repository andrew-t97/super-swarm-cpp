#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Slider {
public:
  /**
   * @brief Constructs a new instance of Slider
   *
   * @param pos The position of the slider
   * @param width The width of the slider
   * @param height The height of the slider
   * @param minValue The minimum value of the slider
   * @param maxValue The maximum value of the slider
   * @param font The font to use for the slider's value text
   */
  Slider(const sf::Vector2f &pos, const float width, const float height,
         const float minValue, const float maxValue, const sf::Font &font);

  /**
   * @brief Handles SFML events for the slider e.g. the mouse dragging the
   * slider left and right.
   *
   * @param event The SFML event to handle
   * @param window The SFML window to handle the event for
   */
  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);

  /**
   * @brief Draws the slider to an SFML window
   *
   * @param window The SFML window to draw the slider to
   */
  virtual void draw(sf::RenderWindow &window) const;

  /**
   * @brief Gets the current value of the slider
   *
   * @return The current value of the slider
   */
  float getValue() const;

  /**
   * @brief Gets the value of the slider normalised between 0 and 1
   *
   * @return The normalised value of the slider
   */
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

  /**
   * @brief Initialises the text that displays the value of the slider.
   *
   * Sets the position, font, character size, fill colour and string of the text
   * which will display the slider's value.
   */
  void initialiseValueText();

  /**
   * @brief Handles the left mouse button pressed event.
   *
   * Checks if the left mouse button is being pressed within the bounds
   * of the slider handle and sets the mouse dragging flag to true.
   *
   * @param event The SFML event to handle
   * @param window The SFML window to handle the event for
   */
  void handleMousePressed(const sf::Event &event,
                          const sf::RenderWindow &window);

  /**
   * @brief Handles the left mouse button released event.
   *
   * Checks if the left mouse button is released and sets the mouse dragging
   * flag to false.
   *
   * @param event The SFML event to handle
   * @param window The SFML window to handle the event for
   */
  void handleMouseReleased(const sf::Event &event,
                           const sf::RenderWindow &window);

  /**
   * @brief Handles the mouse moved event.
   *
   * If the mouse dragging flag is true, will update the handle position
   * according to the mouse's position and updates the current value and value
   * text accordingly.
   *
   * @param event The SFML event to handle
   * @param window The SFML window to handle the event for
   */
  void handleMouseMoved(const sf::Event &event, const sf::RenderWindow &window);

  /**
   * @brief Updates the current value of the slider based on the position of the
   * handle.
   */
  void updateCurrentValue();

  /**
   * @brief Updates the text that displays the value of the slider with its
   * current value.
   */
  void updateValueText();

  /**
   * @brief Updates the slider.
   *
   * Updates the current value of the slider based on its position and then
   * updates the text displaying the current value.
   */
  void update();

  /**
   * @brief Sets the position of the slider handle.
   *
   * Sets the position of the slider handle to the given x position. If the x
   * position is outside the bounds of the slider, it will be clamped to the
   * nearest bound.
   *
   * @param x The new x position of the handle
   */
  void setHandleXPosition(float x);
};
