#include "bird.h"

#define ALIGNMENT_WEIGHT 0.5f
#define COHESION_WEIGHT 0.5f
#define SEPARATION_WEIGHT 0.5f

class BirdSwarm {
public:
  BirdSwarm(const std::vector<Bird> &swarmingBirds);
  void update();
  void render(sf::RenderWindow &window);

private:
  std::vector<Bird> birds;
};