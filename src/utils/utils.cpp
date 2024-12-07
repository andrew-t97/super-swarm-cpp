#include "utils.h"

#include <cmath>

float norm(sf::Vector2f vec) {
  float square_sum = pow(vec.x, 2) + pow(vec.y, 2);
  float norm = sqrt(square_sum);

  return norm;
}

void setVecMag(sf::Vector2f &vec, float mag) {
  float cur_mag = norm(vec);

  if (cur_mag != 0) {
    sf::Vector2f normalisedVec = vec / cur_mag;
    vec = normalisedVec * mag;
  }
}

void limit_vector(sf::Vector2f &vec, float limit) {
  float mag = norm(vec);

  if (mag > limit) {
    sf::Vector2f normalisedVec = vec / mag;
    vec = normalisedVec * limit;
  }
}

void loadFont(sf::Font &font, std::string fontFilePath) {
  if (!font.loadFromFile(fontFilePath)) {
    throw std::runtime_error("Failed to load font");
  }
}
