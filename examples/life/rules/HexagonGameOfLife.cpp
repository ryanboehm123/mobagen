//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {
      Point2D pointToCalculate = {i,j};
      if(world.Get(pointToCalculate)) {
        if(CountNeighbors(world, pointToCalculate) < 2) {
          world.SetNext(pointToCalculate, false);
        } else if (CountNeighbors(world, pointToCalculate) == 2) {
          world.SetNext(pointToCalculate, true);
        } else {
          world.SetNext(pointToCalculate, false);
        }
      }
      else {
        if (CountNeighbors(world, pointToCalculate) == 3) {
          world.SetNext(pointToCalculate, true);
        } else {
          world.SetNext(pointToCalculate, false);
        }
      }
    }
  }
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      Point2D pointNeighbor = {point.x + i, point.y + j};
      if(world.Get(pointNeighbor) && !(i == -1 && j != 0)) {
        count++;
      }
    }
  }
  return count;
}
