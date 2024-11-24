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

// TODO: Validate this works in both negative and positive directions
void limit_vector(sf::Vector2f &vec, float limit) {
  float speed = norm(vec);

  if (speed > limit) {
    vec = (vec / speed) * limit;
  }
}