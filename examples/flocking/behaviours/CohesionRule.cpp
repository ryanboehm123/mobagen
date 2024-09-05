#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerOfMass = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  // find center of mass
  for(const Boid* b : neighborhood) {
    centerOfMass += {b->getPosition().x, b->getPosition().y};
  }
  if(neighborhood.size() > 0) {
    //centerOfMass = Vector2f::normalized(centerOfMass);
    centerOfMass /= neighborhood.size();
    cohesionForce = { centerOfMass.x - boid->getPosition().x, centerOfMass.y - boid->getPosition().y } / boid->getDetectionRadius();
  }

  return Vector2f::normalized(cohesionForce);
}