#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  //todo: implement pathfinding algorithm for the cat
  auto pos = world->getCat();
  std::vector<Point2D> validMoves;
  if(world->catCanMoveToPosition(World::NE(pos))) validMoves.push_back(World::NE(pos));
  if(world->catCanMoveToPosition(World::NW(pos))) validMoves.push_back(World::NW(pos));
  if(world->catCanMoveToPosition(World::E(pos))) validMoves.push_back(World::E(pos));
  if(world->catCanMoveToPosition(World::W(pos))) validMoves.push_back(World::W(pos));
  if(world->catCanMoveToPosition(World::SW(pos))) validMoves.push_back(World::SW(pos));
  if(world->catCanMoveToPosition(World::SE(pos))) validMoves.push_back(World::SE(pos));

  if(validMoves.size() == 0) return pos;

  auto rand = Random::Range(0, validMoves.size() - 1);
  return validMoves.at(rand);
}