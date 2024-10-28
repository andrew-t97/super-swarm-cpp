#include "bird.h"
#include "swarming.h"

#include <cstdlib>
#include <ctime>

#define NEIGHBOURHOOD_RADIUS 2.0f
#define MAX_BIRD_SPEED 0.1f

int main(int argc, char const *argv[]) {
  srand(static_cast<unsigned>(time(0)));

  sf::RenderWindow window(sf::VideoMode(800, 600), "Swarm Demo");
  sf::Vector2u windowSize = window.getSize();

  std::vector<Bird> birds;
  for (int i = 0; i < 100; i++) {
    birds.emplace_back(rand() % 800, rand() % 600);
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    // Update boids
    for (Bird &bird : birds) {
      sf::Vector2f alignment =
          computeAlignment(bird, birds, NEIGHBOURHOOD_RADIUS);
      sf::Vector2f cohesion =
          computeCohesion(bird, birds, NEIGHBOURHOOD_RADIUS);
      sf::Vector2f separation =
          computeSeparation(bird, birds, NEIGHBOURHOOD_RADIUS * 2);

      bird.update(alignment, cohesion, separation, MAX_BIRD_SPEED, windowSize);

      window.draw(bird.shape);
    }

    window.display();
  }

  return 0;
}