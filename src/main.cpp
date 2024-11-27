#include "bird.h"
#include "swarming.h"

#include <cstdlib>
#include <ctime>

#define ALIGN_RADIUS 70.0f
#define COHESEION_RADIUS 70.0f
#define SEPARATION_RADIUS 30.0f
#define MAX_BIRD_SPEED 6.0f
#define NUM_BIRDS 500
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

  std::vector<Bird> birds;
  for (int i = 0; i < NUM_BIRDS; i++) {
    birds.emplace_back(rand() % width, rand() % height);
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    // Update birds
    for (Bird &bird : birds) {
      sf::Vector2f alignment = computeAlignment(
          bird, birds, ALIGN_RADIUS, ALIGNMENT_WEIGHT, MAX_BIRD_SPEED);

      sf::Vector2f cohesion =
          computeCohesion(bird, birds, COHESEION_RADIUS, COHESION_WEIGHT);

      sf::Vector2f separation = computeSeparation(
          bird, birds, SEPARATION_RADIUS, SEPARATION_WEIGHT, MAX_BIRD_SPEED);

      bird.update(alignment, cohesion, separation, MAX_BIRD_SPEED, windowSize);

      window.draw(bird.shape);
    }

    window.display();

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed < timePerFrame) {
      sf::sleep(timePerFrame - elapsed); // Sleep for remaining time of tick
    }

    clock.restart(); // Restart the clock for the next loop
  }

  return 0;
}