#include "bird.h"
#include "bird_swarm.h"
#include "swarming.h"

#include <cstdlib>
#include <ctime>

#define NUM_BIRDS 200

#define ALIGNMENT_PERCENT 0.00008f
#define COHESION_PERCENT 0.00008f
#define SEPARATION_RADIUS 30.0f

#define ALIGNMENT_WEIGHT 0.5f
#define COHESION_WEIGHT 0.5f
#define SEPARATION_WEIGHT 0.5f

#define FPS 60.0f

int main(int argc, char const *argv[]) {
  sf::Clock clock;
  const sf::Time timePerFrame = sf::seconds(1.0f / FPS);

  srand(static_cast<unsigned>(time(0))); // Setting up random

  unsigned int width = sf::VideoMode::getDesktopMode().width;
  unsigned int height = sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(width, height), "Swarm Demo");
  sf::Vector2u windowSize = window.getSize();

  float alignment = windowSize.x * windowSize.y * ALIGNMENT_PERCENT;
  float cohesion = windowSize.x * windowSize.y * COHESION_PERCENT;

  const perceptionRadius perception = {
      alignment,
      cohesion,
      SEPARATION_RADIUS,
  };

  std::vector<Bird> birds;
  for (int i = 0; i < NUM_BIRDS; i++) {
    birds.emplace_back(rand() % width, rand() % height, windowSize, perception);
  }

  birdSwarmWeights weights = {
      ALIGNMENT_WEIGHT,
      COHESION_WEIGHT,
      SEPARATION_WEIGHT,
  };

  BirdSwarm birdSwarm(birds, weights);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    birdSwarm.update();
    birdSwarm.render(window);

    window.display();

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed < timePerFrame) {
      sf::sleep(timePerFrame - elapsed); // Sleep for remaining time of tick
    }

    clock.restart(); // Restart the clock for the next loop
  }

  return 0;
}