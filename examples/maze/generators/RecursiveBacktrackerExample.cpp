#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  std::vector<Point2D> visitables;
  if(stack.size() <= 0) {
    visitables = getVisitables(w, Point2D(0, 0));
    w->SetNodeColor(Point2D(0, 0), Color::White);
    stack.push_back(Point2D(0, 0));
    visited[0][0] = true;
  } else {
    visitables = getVisitables(w, stack.back());
    w->SetNodeColor(stack.back(), Color::White);
  }

  if(visitables.empty()) {
    //return false;
  } else {
    if(visitables.size() == 1) {
      int direction = getDirection(w, stack.back(), visitables.front());
      if(direction == 1) { // North
        w->SetNorth(visitables.front(), true);
      } else if(direction == 2) { // East
        w->SetEast(visitables.front(), true);
      } else if(direction == 3) { // South
        w->SetSouth(visitables.front(), true);
      } else if(direction == 4) { // West
        w->SetWest(visitables.front(), true);
      } else {
        return false;
      }
      visited[visitables.front().x][visitables.front().y] = true;
      stack.push_back(visitables.front());
      return true;
    } else {
      int random = rand() % visitables.size();
      int direction = getDirection(w, stack.back(), visitables.at(random));
      if(direction == 1) { // North
        w->SetNorth(visitables.at(random), true);
      } else if(direction == 2) { // East
        w->SetEast(visitables.at(random), true);
      } else if(direction == 3) { // South
        w->SetSouth(visitables.at(random), true);
      } else if(direction == 4) { // West
        w->SetWest(visitables.at(random), true);
      } else {
        return false;
      }
      visited[visitables.at(random).x][visitables.at(random).y] = true;
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

  if(!visited[p.x][p.y - 1] && w->GetNorth(p) && abs(p.y - 1) <= sideOver2) {
    visitables.push_back(p.Up());
  }
  if(!visited[p.x + 1][p.y] && w->GetEast(p) && abs(p.x + 1) <= sideOver2) {
    visitables.push_back(p.Right());
  }
  if(!visited[p.x][p.y + 1] && w->GetSouth(p) && abs(p.y + 1) <= sideOver2) {
    visitables.push_back(p.Down());
  }
  if(!visited[p.x - 1][p.y] && w->GetWest(p) && abs(p.x - 1) <= sideOver2) {
    visitables.push_back(p.Left());
  }

  return visitables;
}

int RecursiveBacktrackerExample::getDirection(World* w, const Point2D& currentPoint, const Point2D& nextPoint) {
  auto sideOver2 = w->GetSize() / 2;

  if(currentPoint.y + 1 == nextPoint.y) {
    return 1; // North
  } else if (currentPoint.x + 1 == nextPoint.x) {
    return 2; // East
  } else if(currentPoint.y - 1 == nextPoint.y) {
    return 3; // South
  } else if(currentPoint.x - 1 == nextPoint.x) {
    return 4; // West
  } else {
    return 0; // Should never run, here for bugtesting
  }
}