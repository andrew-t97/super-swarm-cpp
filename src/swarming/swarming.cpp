#include "swarming.h"
#include "utils.h"

#include <cmath>

#define MAX_FORCE 0.3f
#define MAX_SEPARATION_FORCE (MAX_FORCE * 1.5f)

bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                               const float neighbourhoodRadius) {
  float distanceBetweenBirds = std::hypot(other.position.x - bird.position.x,
                                          other.position.y - bird.position.y);
  return (distanceBetweenBirds < neighbourhoodRadius);
}

sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float neighbourhoodRadius,
                              const float weight, const float maxSpeed) {
  sf::Vector2f alignment(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {

    if (&bird != &other &&
        isBirdInSameNeighbourhood(bird, other, neighbourhoodRadius)) {
      alignment += other.velocity;
      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    // Taking the average vector (direction)
    alignment /= (float)(no_neighbours);

    // Set magnitude/speed to max
    setVecMag(alignment, maxSpeed);

    // Find the difference between the birds
    alignment -= bird.velocity;

    // Prevent vector exceeding max steering force
    limit_vector(alignment, MAX_FORCE);

    alignment *= weight;
  }

  return alignment;
}

sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float neighbourhoodRadius,
                             const float weight, const float maxSpeed) {
  sf::Vector2f cohesion(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {
    if (&bird != &other &&
        isBirdInSameNeighbourhood(bird, other, neighbourhoodRadius)) {
      cohesion += other.position;
      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    // Taking the average position of all neighbours
    cohesion /= (float)no_neighbours;

    // Finding difference between bird's current position and it's
    // neighbours average position
    cohesion -= bird.position;

    // Prevent vector exceeding max steering force
    limit_vector(cohesion, MAX_FORCE);

    cohesion *= weight;
  }

  return cohesion;
}

sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float separationRadius, const float weight,
                               const float maxSpeed) {
  sf::Vector2f separation(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {
    float distance = std::hypot(other.position.x - bird.position.x,
                                other.position.y - bird.position.y);

    if (&bird != &other && distance < separationRadius) {
      sf::Vector2f difference = bird.position - other.position;

      sf::Vector2f repulsion =
          difference * (float)pow(1 - (norm(difference) / separationRadius), 2);

      separation += repulsion;

      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    separation /= (float)(no_neighbours); // Taking the average separation of
    // all neighbours

    // Set magnitude/speed to max
    setVecMag(separation, maxSpeed);

    separation -= bird.velocity;

    // Prevent vector exceeding max steering force
    limit_vector(separation, MAX_SEPARATION_FORCE);

    separation *= weight;
  }

  return separation;
}