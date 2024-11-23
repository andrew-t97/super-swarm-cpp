#include "utils.h"

#include <cmath>

float norm(sf::Vector2f vec) {
  float square_sum = pow(vec.x, 2) + pow(vec.y, 2);
  float norm = sqrt(square_sum);

  return norm;
}

// TODO: Validate this works in both negative and positive directions
void cap_vector_to_max_speed(sf::Vector2f &vec, float maxSpeed) {
  float speed = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));

  if (speed > maxSpeed) {
    vec = (vec / speed) * maxSpeed;
  }
}