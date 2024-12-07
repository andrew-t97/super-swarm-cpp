#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Calculates the norm of a vector
 *
 * @param vec the vector to calculate the norm of
 * @return The norm of the vector
 */
float norm(sf::Vector2f &vec);

/**
 * @brief Limits the magnitude of a vector
 *
 * @param vec The vector to limit
 * @param limit The limit to apply to the vector
 */
void limit_vector(sf::Vector2f &vec, float limit);

/**
 * @brief Sets the magnitude of a vector
 *
 * @param vec The vector to set the magnitude of
 * @param mag The magnitude to set the vector to
 */
void setVecMag(sf::Vector2f &vec, float mag);

/**
 * @brief Loads a font from a file path into an SFML font object
 *
 * @param font The font object to load the font into
 * @param fontFilePath The file path to the font
 */
void loadFont(sf::Font &font, std::string fontFilePath);