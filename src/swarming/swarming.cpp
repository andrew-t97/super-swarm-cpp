#include "swarming.h"
#include "utils.h"

#include <cmath>

bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                               const float neighbourhoodRadius) {
  float distanceBetweenBirds = std::hypot(other.position.x - bird.position.y,
                                          other.position.y - bird.position.y);
  return (distanceBetweenBirds < neighbourhoodRadius);
}

// TODO: Add normalisation and weight
sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float neighbourhoodRadius) {
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
        no_neighbours);         // Taking the average vector (direction)
    alignment -= bird.velocity; // Finding the difference between the birds
                                // current direction and the group direction
                                // (steering strength of alignment)
  }

  return alignment;
}

// TODO: Add normalisation and weight
sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float neighbourhoodRadius) {
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
    cohesion -= bird.velocity; // Calculating the steering strength to be
                               // applied to the birds velocity
  }

  return cohesion;
}

sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float separationRadius,
                               const float weight) {
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
    sf::Vector2f normalisedSeparation = separation / norm(separation);
    separation = normalisedSeparation * weight;
  }

  return separation;
}