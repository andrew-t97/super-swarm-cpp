#include "bird_swarm.h"
#include "swarming.h"

#define ALIGNMENT_RADIUS 70.0f
#define COHESEION_RADIUS 70.0f
#define SEPARATION_RADIUS 30.0f

BirdSwarm::BirdSwarm(const std::vector<Bird> &swarmingBirds)
    : birds(swarmingBirds) {}

void BirdSwarm::update() {

  for (Bird &bird : birds) {
    sf::Vector2f alignment = computeAlignment(bird, birds, ALIGNMENT_WEIGHT);

    sf::Vector2f cohesion = computeCohesion(bird, birds, COHESION_WEIGHT);

    sf::Vector2f separation = computeSeparation(bird, birds, SEPARATION_WEIGHT);

    sf::Vector2f acceleration = alignment + cohesion + separation;

    bird.update(acceleration);
  }
}

void BirdSwarm::render(sf::RenderWindow &window) {
  for (Bird &bird : birds) {
    bird.render(window);
  }
}
