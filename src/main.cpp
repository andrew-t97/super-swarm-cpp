#include "bird.h"
#include "bird_swarm.h"
#include "config.h"
#include "swarming.h"
#include "utils.h"
#include "weight_slider.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

// Change these to constexprs
#define NUM_BIRDS 200

#define SEPARATION_PERCEPTION_RADIUS 30.0f

#define SLIDER_HEIGHT 40
#define SLIDER_WIDTH 200
#define SLIDER_VERTICLE_SPACING 10
#define SLIDER_VERTICLE_OFFSET (SLIDER_HEIGHT + SLIDER_VERTICLE_SPACING)
#define SLIDERS_VERTICLE_POSITION 10
#define SLIDERS_HORIZONTAL_POSITION 20
#define MAX_COLOUR 255

#define FPS 60.0f

std::vector<Bird> createBirds(sf::Vector2u windowSize) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed generator

  std::uniform_int_distribution<> colourDistr(0, MAX_COLOUR);

  std::uniform_real_distribution<> widthDistr(windowSize.x);
  std::uniform_real_distribution<> heightDistr(windowSize.y);
  std::uniform_real_distribution<> velocityDistr(-Bird::maxSpeed,
                                                 Bird::maxSpeed);

  std::vector<Bird> birds;
  for (int i = 0; i < NUM_BIRDS; i++) {
    sf::Color colour(colourDistr(gen), colourDistr(gen), colourDistr(gen));
    sf::Vector2f birdPosition(widthDistr(gen), heightDistr(gen));
    sf::Vector2f velocity(velocityDistr(gen), velocityDistr(gen));

    birds.emplace_back(birdPosition, windowSize, colour, velocity);
  }

  return birds;
}

// TODO: Fix swarming tests
// TODO: Refactor things in here

typedef struct {
  BasicSliderWithTitle alignment;
  BasicSliderWithTitle cohesion;
  BasicSliderWithTitle separation;
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

  sf::Font font;
  loadFont(font, std::string(Config::FONT_FILE_NAME));

  weightSliders sliders = {
      BasicSliderWithTitle(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION, SLIDERS_VERTICLE_POSITION),
          SLIDER_WIDTH, SLIDER_HEIGHT, font, "Alignment"),
      BasicSliderWithTitle(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION,
                       SLIDERS_VERTICLE_POSITION + SLIDER_VERTICLE_OFFSET),
          SLIDER_WIDTH, SLIDER_HEIGHT, font, "Cohesion"),
      BasicSliderWithTitle(
          sf::Vector2f(SLIDERS_HORIZONTAL_POSITION,
                       SLIDERS_VERTICLE_POSITION + SLIDER_VERTICLE_OFFSET * 2),
          SLIDER_WIDTH, SLIDER_HEIGHT, font, "Separation"),
  };

  float alignmentPerception = std::min(windowSize.x, windowSize.y) * 0.075;
  float cohesionPerception = std::min(windowSize.x, windowSize.y) * 0.075;

  const swarmPerceptionRadii perception = {
      alignmentPerception,
      cohesionPerception,
      SEPARATION_PERCEPTION_RADIUS,
  };

  birdSwarmWeights weights = {
      sliders.alignment.getValue(),
      sliders.cohesion.getValue(),
      sliders.separation.getValue(),
  };

  const std::vector<Bird> birds = createBirds(windowSize);
  BirdSwarm birdSwarm(birds, perception, weights);

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

    weights.alignment = sliders.alignment.getNormalizedValue();
    weights.cohesion = sliders.cohesion.getNormalizedValue();
    weights.separation = sliders.separation.getNormalizedValue();

    birdSwarm.setWeights(weights);
    birdSwarm.update();
    birdSwarm.draw(window);

    window.display();

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed < timePerFrame) {
      sf::sleep(timePerFrame - elapsed); // Sleep for remaining time of tick
    }

    clock.restart(); // Restart the clock for the next loop
  }

  return 0;
}