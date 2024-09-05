#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  Vector2f calculatedVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  for(const Boid* b : neighborhood) {
    calculatedVelocity += {b->getVelocity().x, b->getVelocity().y};
  }
  if(neighborhood.size() > 0) {
    calculatedVelocity = Vector2f::normalized(calculatedVelocity);
    averageVelocity = calculatedVelocity / neighborhood.size();
  }

  return Vector2f::normalized(averageVelocity);
}