#pragma once

#include "bird.h"
#include <SFML/Graphics.hpp>

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
 * @return true If the other bird is within the neighbourhood radius of the
 * reference bird.
 * @return false If the other bird is outside the neighbourhood radius of the
 * reference bird.
 */
bool isBirdInSameNeighbourhood(const Bird &bird, const Bird &other,
                               const float neighbourhoodRadius);

/**
 * @brief Computes the alignment force for a given bird based on its neighbors.
 *
 * This function calculates the alignment force for a bird, which is a steering
 * behavior that causes the bird to align its direction with the average
 * direction of its neighboring birds within a specified radius. The alignment
 * force helps the bird to move in a cohesive manner with its flock.
 *
 * @param bird The bird for which the alignment force is being computed.
 * @param birds A vector containing all the birds in the flock.
 * @param neighbourhoodRadius The radius within which neighboring birds are
 * considered.
 * @param maxSpeed The maximum speed that a bird can achieve.
 * @return A 2D vector representing the alignment force to be applied to the
 * bird.
 */
sf::Vector2f computeAlignment(const Bird &bird, const std::vector<Bird> &birds,
                              const float neighbourhoodRadius,
                              const float weight, const float maxSpeed);

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
 * @param neighbourhoodRadius The radius within which neighboring birds are
 * considered.
 * @param maxSpeed The maximum speed a bird can achieve.
 * @return A vector representing the cohesion force to be applied to the bird.
 */
sf::Vector2f computeCohesion(const Bird &bird, const std::vector<Bird> &birds,
                             const float neighbourhoodRadius,
                             const float weight, float maxSpeed);

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
 * @param separationRadius The radius within which the bird should maintain
 * separation from other birds.
 * @param maxSpeed The maximum speed that the bird can achieve.
 * @return A vector representing the separation force to be applied to the bird.
 */
sf::Vector2f computeSeparation(const Bird &bird, const std::vector<Bird> &birds,
                               const float separationRadius, const float weight,
                               const float maxSpeed);