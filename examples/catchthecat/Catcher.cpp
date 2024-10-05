#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  auto catPos = world->getCat();
  std::vector<Point2D> path = generatePath(world);
  if(path.size() != 0) {
    return path.front();
  }
  std::vector<Point2D> validMoves;
  if(!world->getContent(world->NW(catPos))) validMoves.push_back(world->NW(catPos));
  if(!world->getContent(world->NE(catPos))) validMoves.push_back(world->NE(catPos));
  if(!world->getContent(world->SW(catPos))) validMoves.push_back(world->SW(catPos));
  if(!world->getContent(world->SE(catPos))) validMoves.push_back(world->SE(catPos));
  if(!world->getContent(world->E(catPos))) validMoves.push_back(world->E(catPos));
  if(!world->getContent(world->W(catPos))) validMoves.push_back(world->W(catPos));

  if(validMoves.size() == 0) return catPos;

  auto rand = Random::Range(0, validMoves.size() - 1);
  return validMoves.at(rand);
}
