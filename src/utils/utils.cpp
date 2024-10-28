#include "utils.h"

// TODO: Validate this works in both negative and positive directions
void cap_vector_to_max_speed(sf::Vector2f &vec, float maxSpeed) {
  float speed = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));

  if (speed > maxSpeed) {
    vec = (vec / speed) * maxSpeed;
  }
}