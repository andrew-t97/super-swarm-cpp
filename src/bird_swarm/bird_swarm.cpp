#include "bird_swarm.h"
#include "swarming.h"

BirdSwarm::BirdSwarm(const std::vector<Bird> &swarmingBirds,
                     birdSwarmWeights &weights)
    : birds(swarmingBirds), swarmWeights(weights) {}

void BirdSwarm::update() {

  for (Bird &bird : birds) {
    sf::Vector2f alignment =
        computeAlignment(bird, birds, swarmWeights.alignment);

    sf::Vector2f cohesion = computeCohesion(bird, birds, swarmWeights.cohesion);

    sf::Vector2f separation =
        computeSeparation(bird, birds, swarmWeights.separation);

    sf::Vector2f acceleration = alignment + cohesion + separation;

    bird.update(acceleration);
  }
}

void BirdSwarm::render(sf::RenderWindow &window) {
  for (Bird &bird : birds) {
    bird.render(window);
  }
}

bool BirdSwarm::isWeightValid(float &weight) {
  return 0.0f <= weight && weight <= 1.0f;
}

void BirdSwarm::setWeights(birdSwarmWeights &weights) {
  if (isWeightValid(weights.alignment) && isWeightValid(weights.cohesion) &&
      isWeightValid(weights.separation)) {
    swarmWeights = weights;
  } else {
    throw std::out_of_range("Weights must be between 0 and 1");
  }
}
