#pragma once

#include "bird.h"
#include "swarming.h"

typedef struct {
  float alignment;
  float cohesion;
  float separation;
} birdSwarmWeights;

/**
 * @brief A collection of birds which swarm together based on alignment,
 * cohesion, and separation
 *
 *
 * This class manages a collection of birds, applying alignment,
 * cohesion, and separation forces to each bird so that they follow a swarming
 * pattern.
 *
 * - Alignment: Birds will steer towards the average heading of their neighbours
 *
 * - Cohesion: Birds will steer towards the average position of their neighbours
 *
 * - Separation: Birds will steer away from eachother to avoid crowding their
 * neighbours
 */
class BirdSwarm {

public:
  /**
   * @brief Constructs a new Bird Swarm object
   *
   * @param swarmingBirds The collection of birds that will be part of the swarm
   * @param perceptionRadii The radius for each of the components of the
   * swarming behaviour i.e. alignment, cohesion, separation for each bird.
   * @param weights The weights for alignment, cohesion, and separation
   */
  BirdSwarm(const std::vector<Bird> &swarmingBirds,
            const swarmPerceptionRadii &perceptionRadii,
            birdSwarmWeights &weights);

  /**
   * @brief Calculates a new set of forces and updates the bird positions.
   *
   * Calculates a new set of alignment, cohesion, and separation forces
   * for each bird and updates their positions based upon these forces.
   */
  void update();

  /**
   * @brief Draws each bird in the swarm in the provided render window.
   *
   * @param window The window to draw the swarm's birds in.
   */
  void draw(sf::RenderWindow &window);

  /**
   * @brief Sets the swarm weights to the provided weights
   *
   * Sets the swarm weights, alignment, cohesion, separation to the provided
   * weights.
   *
   * @param weights The weights to set the swarm's weights to.
   */
  void setWeights(birdSwarmWeights &weights);

private:
  birdSwarmWeights swarmWeights;
  swarmPerceptionRadii perceptionRadii;
  std::vector<Bird> birds;

  /**
   * @brief Checks if the provided weight is valid
   *
   * @param weight The weight to check
   *
   * @return true if the weight is between 0 and 1 (inclusive), false otherwise.
   */
  bool isWeightValid(float weight);
};