#include "bird.h"

typedef struct {
  float alignment;
  float cohesion;
  float separation;
} birdSwarmWeights;

class BirdSwarm {
public:
  BirdSwarm(const std::vector<Bird> &swarmingBirds, birdSwarmWeights &weights);
  void update();
  void render(sf::RenderWindow &window);
  void setWeights(birdSwarmWeights &weights);

private:
  birdSwarmWeights swarmWeights;
  std::vector<Bird> birds;
  bool isWeightValid(float &weight);
};