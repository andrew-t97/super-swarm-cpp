#include "swarming.h"
#include "utils.h"

#include <cmath>

constexpr float maxForce = 0.3f;
constexpr float maxSeparationForce = maxForce * 1.5f;

bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                               const float neighbourhoodRadius) {
  float distanceBetweenBirds = std::hypot(other.position.x - bird.position.x,
                                          other.position.y - bird.position.y);
  return (distanceBetweenBirds < neighbourhoodRadius);
}

sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float perceptionRadius,
                              const float weight) {
  sf::Vector2f alignment(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {

    if (&bird != &other &&
        isBirdInSameNeighbourhood(bird, other, perceptionRadius)) {
      alignment += other.velocity;
      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    alignment /= (float)(no_neighbours);

    // Set magnitude/speed to max to keep momentum
    setVecMag(alignment, bird.maxSpeed);

    alignment -= bird.velocity;

    limit_vector(alignment, maxForce);

    alignment *= weight;
  }

  return alignment;
}

sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float perceptionRadius, const float weight) {
  sf::Vector2f cohesion(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {
    if (&bird != &other &&
        isBirdInSameNeighbourhood(bird, other, perceptionRadius)) {
      cohesion += other.position;
      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    cohesion /= (float)no_neighbours;

    // Finding difference between bird's current position and it's
    // neighbours average position
    cohesion -= bird.position;

    limit_vector(cohesion, maxForce);

    cohesion *= weight;
  }

  return cohesion;
}

sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float perceptionRadius,
                               const float weight) {
  sf::Vector2f separation(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {
    float distance = std::hypot(other.position.x - bird.position.x,
                                other.position.y - bird.position.y);

    if (&bird != &other &&
        isBirdInSameNeighbourhood(bird, other, perceptionRadius)) {
      sf::Vector2f difference = bird.position - other.position;

      sf::Vector2f repulsion =
          difference * (float)pow(1 - (norm(difference) / perceptionRadius), 2);

      separation += repulsion;

      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    separation /= (float)(no_neighbours);

    // Set magnitude/speed to max to keep momentum
    setVecMag(separation, bird.maxSpeed);

    separation -= bird.velocity;

    limit_vector(separation, maxSeparationForce);

    separation *= weight;
  }

  return separation;
}