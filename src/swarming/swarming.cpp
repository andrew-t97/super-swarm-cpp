#include "swarming.h"
#include "bird.h"
#include "utils.h"

static bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                                      const float neighbourhoodRadius) {
  float distanceBetweenBirds = std::hypot(other.position.x - bird.position.y,
                                          other.position.y - bird.position.y);
  return (distanceBetweenBirds < neighbourhoodRadius);
}

sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float neighbourhoodRadius,
                              const float maxSpeed) {
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
    alignment /= static_cast<float>(
        no_neighbours); // Taking the average vector (direction)
    cap_vector_to_max_speed(alignment, maxSpeed);
    alignment -= bird.velocity; // Finding the difference between the birds
                                // current direction and the group direction
                                // (steering strength of alignment)
  }

  return alignment;
}

sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float neighbourhoodRadius,
                             const float maxSpeed) {
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
    cohesion /= static_cast<float>(
        no_neighbours);        // Taking the average position of all neighbours
    cohesion -= bird.position; // Finding difference between bird's current
                               // position and it's neighbours average position
    cap_vector_to_max_speed(cohesion, maxSpeed);
    cohesion -= bird.velocity; // Calculating the steering strength to be
                               // applied to the birds velocity
  }

  return cohesion;
}

sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float separationRadius,
                               const float maxSpeed) {
  sf::Vector2f separation(0.0f, 0.0f);
  int no_neighbours = 0;

  for (const Bird &other : birds) {
    float distance = std::hypot(other.position.x - bird.position.x,
                                other.position.y - bird.position.y);

    if (&bird != &other && distance < separationRadius) {
      sf::Vector2f repulsion = bird.position - other.position;

      if (distance > 0)
        repulsion /= distance; // repulsion is weighted by proximity

      separation += repulsion;
      ++no_neighbours;
    }
  }

  if (no_neighbours > 0) {
    separation /= static_cast<float>(
        no_neighbours); // Taking the average separation of all neighbours
    cap_vector_to_max_speed(separation, maxSpeed);
    separation -= bird.velocity; // Calculates the steering force to be applied
                                 // to the bird's current velocity
  }

  return separation;
}