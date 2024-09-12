//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {
      Point2D pointToCalculate = {i,j};
      if(world.Get(pointToCalculate)) {
        if(CountNeighbors(world, pointToCalculate) <= 1) {
          world.SetNext(pointToCalculate, false);
        } else if (CountNeighbors(world, pointToCalculate) == 2) {
          world.SetNext(pointToCalculate, true);
        } else {
          world.SetNext(pointToCalculate, false);
        }
      }
      else {
        if (CountNeighbors(world, pointToCalculate) == 2) {
          world.SetNext(pointToCalculate, true);
        } else {
          world.SetNext(pointToCalculate, false);
        }
      }
    }
  }
}

bool topLeft(World& world, Point2D point) {
  if(point.y % 2 == 0) {
    return world.Get({point.x-1, point.y-1});
  } else {
    return world.Get({point.x, point.y-1});
  }
}

bool topRight(World& world, Point2D point) {
  if(point.y % 2 == 0) {
    return world.Get({point.x, point.y-1});
  } else {
    return world.Get({point.x+1, point.y-1});
  }
}

bool bottomLeft(World& world, Point2D point) {
  if(point.y % 2 == 0) {
    return world.Get({point.x-1, point.y+1});
  } else {
    return world.Get({point.x, point.y+1});
  }
}

bool bottomRight(World& world, Point2D point) {
  if(point.y % 2 == 0) {
    return world.Get({point.x, point.y+1});
  } else {
    return world.Get({point.x+1, point.y+1});
  }
}

bool right(World& world, Point2D point) {
  return world.Get({point.x+1, point.y});
}

bool left (World& world, Point2D point) {
 return world.Get({point.x-1, point.y});
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int count = 0;

  if(topLeft(world, point)) { count++; }
  if(topRight(world, point)) { count++; }
  if(bottomLeft(world, point)) { count++; }
  if(bottomRight(world, point)) { count++; }
  if(left(world, point)) { count++; }
  if(right(world, point)) { count++; }

  return count;
}
