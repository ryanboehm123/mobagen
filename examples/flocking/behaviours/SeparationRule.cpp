#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  for(const Boid* b : neighborhood) {
    //remove itself
    if(boid->getPosition().x == b->getPosition().x && boid->getPosition().y == b->getPosition().y) {
      continue;
    }
    //calculate the sep vector
    Vector2f sepVec = boid->getPosition() - b->getPosition();
    float dist = sepVec.getMagnitude();
    //if it is inside the sep radius, accumulate the force
    if(dist < desiredMinimalDistance && dist > 0.01f) {
      //normalize the sep vector
      sepVec /= dist;
      float force = 1/dist;
      force *= desiredMinimalDistance;
      separatingForce += sepVec * force;
    }
  }

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
