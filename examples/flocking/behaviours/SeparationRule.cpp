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
    Vector2f sepVec = { boid->getPosition().x - b->getPosition().x, boid->getPosition().y - b->getPosition().y };
    float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);
    //if it is inside the sep radius, accumulate the force
    if(dist < desiredMinimalDistance && dist > 0.01f) {
      //normalize the sep vector
      sepVec = { sepVec.x/dist, sepVec.y/dist };
      float force = 1/dist;
      separatingForce = { separatingForce.x + sepVec.x * force, separatingForce.y + sepVec.y * force };
    }
  }

  separatingForce = Vector2f::normalized(separatingForce);

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
