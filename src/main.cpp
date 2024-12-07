#include "bird.h"
#include "bird_swarm.h"
#include "swarming.h"
#include "utils.h"
#include "weight_slider.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

// Change these to constexprs

namespace SimConfig {
constexpr int numBirds = 200;
constexpr float fps = 60.0f;
constexpr float separationRadiusRatio = 0.025;
constexpr float cohesionRadiusRatio = 0.075;
constexpr float alignmentRadiusRatio = 0.075;
} // namespace SimConfig

namespace GraphicalConfig {
constexpr std::string_view fontFileName = "arial.ttf";
constexpr int sliderHeight = 40;
constexpr int sliderWidth = 200;
constexpr int sliderVerticalSpacing = 10;
constexpr int sliderVerticalOffset = sliderHeight + sliderVerticalSpacing;
constexpr int sliderPositionX = sliderVerticalSpacing;
constexpr int sliderPositionY = 20;
constexpr int maxColor = 255;
} // namespace GraphicalConfig

typedef struct {
  BasicSliderWithTitle alignment;
  BasicSliderWithTitle cohesion;
  BasicSliderWithTitle separation;
} weightSliders;

std::vector<Bird> createBirds(sf::Vector2u windowSize) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed generator

  std::uniform_int_distribution<> colourDistr(0, GraphicalConfig::maxColor);

  std::uniform_real_distribution<> widthDistr(windowSize.x);
  std::uniform_real_distribution<> heightDistr(windowSize.y);
  std::uniform_real_distribution<> velocityDistr(-Bird::maxSpeed,
                                                 Bird::maxSpeed);

  std::vector<Bird> birds;
  for (int i = 0; i < SimConfig::numBirds; i++) {
    sf::Color colour(colourDistr(gen), colourDistr(gen), colourDistr(gen));
    sf::Vector2f birdPosition(widthDistr(gen), heightDistr(gen));
    sf::Vector2f velocity(velocityDistr(gen), velocityDistr(gen));

    birds.emplace_back(birdPosition, windowSize, colour, velocity);
  }

  return birds;
}

weightSliders createSliders(sf::Font &font) {
  return {
      BasicSliderWithTitle(sf::Vector2f(GraphicalConfig::sliderPositionX,
                                        GraphicalConfig::sliderPositionY),
                           GraphicalConfig::sliderWidth,
                           GraphicalConfig::sliderHeight, font, "Alignment"),

      BasicSliderWithTitle(
          sf::Vector2f(GraphicalConfig::sliderPositionX,
                       GraphicalConfig::sliderPositionY +
                           GraphicalConfig::sliderVerticalOffset),
          GraphicalConfig::sliderWidth, GraphicalConfig::sliderHeight, font,
          "Cohesion"),

      BasicSliderWithTitle(
          sf::Vector2f(GraphicalConfig::sliderPositionX,
                       GraphicalConfig::sliderPositionY +
                           GraphicalConfig::sliderVerticalOffset * 2),
          GraphicalConfig::sliderWidth, GraphicalConfig::sliderHeight, font,
          "Separation"),
  };
}

void handleEvents(sf::RenderWindow &window, weightSliders &sliders) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }

  sliders.alignment.handleEvent(event, window);
  sliders.cohesion.handleEvent(event, window);
  sliders.separation.handleEvent(event, window);
}

void draw(sf::RenderWindow &window, weightSliders &sliders,
          BirdSwarm birdSwarm) {
  sliders.alignment.draw(window);
  sliders.cohesion.draw(window);
  sliders.separation.draw(window);

  birdSwarm.draw(window);
}

int main(int argc, char const *argv[]) {
  sf::Clock clock;
  const sf::Time timePerFrame = sf::seconds(1.0f / SimConfig::fps);

  srand(static_cast<unsigned>(time(0))); // Setting up random

  unsigned int width = sf::VideoMode::getDesktopMode().width;
  unsigned int height = sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(width, height), "Swarm Demo");
  sf::Vector2u windowSize = window.getSize();

  sf::Font font;
  loadFont(font, std::string(GraphicalConfig::fontFileName));

  float alignmentPerception =
      std::min(windowSize.x, windowSize.y) * SimConfig::alignmentRadiusRatio;
  float cohesionPerception =
      std::min(windowSize.x, windowSize.y) * SimConfig::cohesionRadiusRatio;
  float separationPerception =
      std::min(windowSize.x, windowSize.y) * SimConfig::separationRadiusRatio;

  const swarmPerceptionRadii perception = {
      alignmentPerception, cohesionPerception, separationPerception};

  weightSliders sliders = createSliders(font);
  birdSwarmWeights weights = {
      sliders.alignment.getValue(),
      sliders.cohesion.getValue(),
      sliders.separation.getValue(),
  };

  const std::vector<Bird> birds = createBirds(windowSize);
  BirdSwarm birdSwarm(birds, perception, weights);

  while (window.isOpen()) {

    handleEvents(window, sliders);

    window.clear();

    weights.alignment = sliders.alignment.getNormalizedValue();
    weights.cohesion = sliders.cohesion.getNormalizedValue();
    weights.separation = sliders.separation.getNormalizedValue();

    birdSwarm.setWeights(weights);
    birdSwarm.update();

    draw(window, sliders, birdSwarm);

    window.display();

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed < timePerFrame) {
      sf::sleep(timePerFrame - elapsed);
    }

    clock.restart();
  }

  return 0;
}