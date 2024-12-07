#pragma once

#include "bird.h"
#include <SFML/Graphics.hpp>

typedef struct {
  const float alignmentRadius;
  const float cohesionRadius;
  const float separationRadius;
} swarmPerceptionRadii;

/**
 * @brief Checks if one bird is within the same neighbourhood radius of another
 * bird.
 *
 * This function determines whether the distance between two birds is within a
 * specified neighbourhood radius.
 *
 * @param bird The reference bird whose neighbourhood is being checked.
 * @param other The other bird to check if it is within the neighbourhood
 * radius.
 * @param neighbourhoodRadius The radius within which the other bird must be to
 * be considered in the same neighbourhood.
 * @return Returns true if the other bird is within the neighbourhood radius of
 * the reference bird otherwise returns false.
 */
bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                               const float neighbourhoodRadius);

/**
 * @brief Computes the alignment force for a given bird based on its neighbors.
 *
 * This function calculates the alignment force for a bird, which is a steering
 * behavior that causes the bird to align its direction with the average
 * direction of its neighboring birds within a specified radius. The alignment
 * force helps the bird to move in the same direction as the others in its
 * flock.
 *
 * @param bird The bird for which the alignment force is being computed.
 * @param birds A vector containing all the birds in the flock.
 * @param perceptionRadius The radius within which other birds are considered in
 * the alignment force calculation.
 * @param weight The weight to apply to the alignment force, larger values
 * increase the force.
 * @return A vector representing the alignment force to be applied to the bird.
 *
 */
sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float perceptionRadius, const float weight);

/**
 * @brief Computes the cohesion vector for a given bird within a flock.
 *
 * This function calculates the cohesion vector for a bird, which is the
 * direction towards the average position of neighboring birds within a
 * specified radius. Cohesion helps to keep the flock together by steering
 * each bird towards the center of mass of its neighbors.
 *
 * @param bird The bird for which the cohesion vector is being computed.
 * @param birds A vector containing all the birds in the flock.
 * @param perceptionRadius The radius within which other birds are considered in
 * the cohesion force calculation.
 * @param weight The weight to apply to the cohesion force, larger values
 * increase the force.
 * @return A vector representing the cohesion force to be applied to the bird.
 */
sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float perceptionRadius, const float weight);

/**
 * @brief Computes the separation force for a given bird to avoid crowding local
 * flockmates.
 *
 * This function calculates a vector that represents the separation force for a
 * bird, which helps it to steer away from nearby birds within a specified
 * separation radius. The separation force is intended to prevent the bird from
 * colliding with or getting too close to other birds in the flock.
 *
 * @param bird The bird for which the separation force is being computed.
 * @param birds A vector containing all the birds in the flock.
 * @param perceptionRadius The radius within which other birds are considered in
 * the separation force calculation.
 * @param weight The weight to apply to the separation force, larger values
 * increase the force.
 * @return A vector representing the separation force to be applied to the bird.
 */
sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float perceptionRadius,
                               const float weight);