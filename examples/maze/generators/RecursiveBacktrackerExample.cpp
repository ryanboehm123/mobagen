#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  std::vector<Point2D> visitables;
  if(stack.size() <= 0) {
    visitables = getVisitables(w, Point2D(0, 0));
    w->SetNodeColor(Point2D(0, 0), Color::Red);
  } else {
    visitables = getVisitables(w, stack.back());
    w->SetNodeColor(stack.back(), Color::Red);
  }

  if(visitables.empty()) {
    //return false;
  } else {
    if(visitables.size() == 1) {
      stack.push_back(visitables.front());
      return true;
    } else {
      int random = rand() % visitables.size();
      stack.push_back(visitables.at(random));
      return true;
    }
  }
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if(w->GetNode(p).GetNorth() && p.y < sideOver2) {
    visitables.push_back(p.Up());
  }
  if(w->GetNode(p).GetEast() && p.x < sideOver2) {
    visitables.push_back(p.Right());
  }
  if(w->GetNode(p).GetSouth() && p.y < sideOver2) {
    visitables.push_back(p.Down());
  }
  if(w->GetNode(p).GetWest() && p.x < sideOver2) {
    visitables.push_back(p.Left());
  }

  return visitables;
}
