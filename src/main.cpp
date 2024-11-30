#include "bird.h"
#include "bird_swarm.h"
#include "swarming.h"
#include "weight_slider.h"

#include <cstdlib>
#include <ctime>

#define NUM_BIRDS 200

#define ALIGNMENT_PERCEPTION_PERCENT_OF_WIN 0.00008f
#define COHESION_PERCEPTION_PERCENT_OF_WIN 0.00008f
#define SEPARATION_PERCEPTION_RADIUS 30.0f

#define SLIDER_HEIGHT 40
#define SLIDER_WIDTH 200
#define SLIDER_VERTICLE_SPACING 10
#define SLIDER_VERTICLE_OFFSET (SLIDER_HEIGHT + SLIDER_VERTICLE_SPACING)
#define SLIDERS_VERTICLE_POSITION 10
#define SLIDERS_HORIZONTAL_POSITION 20

#define FPS 60.0f

typedef struct {
  WeightSlider alignment;
  WeightSlider cohesion;
  WeightSlider separation;
} weightSliders;

int main(int argc, char const *argv[]) {
  sf::Clock clock;
  const sf::Time timePerFrame = sf::seconds(1.0f / FPS);

  srand(static_cast<unsigned>(time(0))); // Setting up random

  unsigned int width = sf::VideoMode::getDesktopMode().width;
  unsigned int height = sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(width, height), "Swarm Demo");
  sf::Vector2u windowSize = window.getSize();

  std::string t = "Test weight slider";

  weightSliders sliders = {
      WeightSlider(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION, SLIDERS_VERTICLE_POSITION),
          SLIDER_WIDTH, SLIDER_HEIGHT, "Alignment"),
      WeightSlider(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION,
                       SLIDERS_VERTICLE_POSITION + SLIDER_VERTICLE_OFFSET),
          SLIDER_WIDTH, SLIDER_HEIGHT, "Cohesion"),
      WeightSlider(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION,
                       SLIDERS_VERTICLE_POSITION + SLIDER_VERTICLE_OFFSET * 2),
          SLIDER_WIDTH, SLIDER_HEIGHT, "Separation"),
  };

  float alignmentPerception =
      windowSize.x * windowSize.y * ALIGNMENT_PERCEPTION_PERCENT_OF_WIN;
  float cohesionPerception =
      windowSize.x * windowSize.y * COHESION_PERCEPTION_PERCENT_OF_WIN;

  const perceptionRadius perception = {
      alignmentPerception,
      cohesionPerception,
      SEPARATION_PERCEPTION_RADIUS,
  };

  std::vector<Bird> birds;
  for (int i = 0; i < NUM_BIRDS; i++) {
    birds.emplace_back(rand() % width, rand() % height, windowSize, perception);
  }

  birdSwarmWeights weights = {
      sliders.alignment.getValue(),
      sliders.cohesion.getValue(),
      sliders.separation.getValue(),
  };

  BirdSwarm birdSwarm(birds, weights);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sliders.alignment.handleEvent(event, window);
    sliders.cohesion.handleEvent(event, window);
    sliders.separation.handleEvent(event, window);

    window.clear();

    // Draw all sliders
    sliders.alignment.draw(window);
    sliders.cohesion.draw(window);
    sliders.separation.draw(window);

    weights.alignment = sliders.alignment.getValue();
    weights.cohesion = sliders.cohesion.getValue();
    weights.separation = sliders.separation.getValue();

    birdSwarm.setWeights(weights);
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