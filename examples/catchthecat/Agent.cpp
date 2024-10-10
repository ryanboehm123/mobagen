#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
#include "../../cmake-build-debug/_deps/sdl2-src/src/render/software/SDL_draw.h"
using namespace std;
int distanceToClosestBorder(World* w, Point2D catPos) {
  int sideSizeOver2 = w->getWorldSideSize() / 2;
  if(catPos.x >= ABS(catPos.y)) {
    return sideSizeOver2 - catPos.x;
  } else if(catPos.x < -ABS(catPos.y)) {
    return sideSizeOver2 + catPos.x;
  } else if(catPos.y >= ABS(catPos.x)) {
    return sideSizeOver2 - catPos.y;
  } else {
    return sideSizeOver2 + catPos.y;
  }
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<AStarNode> frontier;                   // to store next ones to visit
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(AStarNode(catPos, 1, distanceToClosestBorder(w, catPos)));
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
  AStarNode current = frontier.front();
  frontier.pop();

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    visited[current.position] = true;
    vector<AStarNode> visitableNeighbors;
    int sideSize = w->getWorldSideSize();
    if(ABS(current.position.x) >= sideSize/2 || ABS(current.position.y) == sideSize/2) {
      borderExit = current.position;
      while(!frontier.empty()) {
        frontier.pop();
      }
      break;
    }
    if(!visited[w->NW(current.position)] && !w->getContent(w->NW(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->NW(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->NW(current.position))));
      visited[w->NW(current.position)] = true;
    }
    if(!visited[w->NE(current.position)] && !w->getContent(w->NE(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->NE(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->NE(current.position))));
      visited[w->NE(current.position)] = true;
    }
    if(!visited[w->SW(current.position)] && !w->getContent(w->SW(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->SW(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->SW(current.position))));
      visited[w->SW(current.position)] = true;
    }
    if(!visited[w->SE(current.position)] && !w->getContent(w->SE(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->SE(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->SE(current.position))));
      visited[w->SE(current.position)] = true;
    }
    if(!visited[w->E(current.position)] && !w->getContent(w->E(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->E(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->E(current.position))));
      visited[w->E(current.position)] = true;
    }
    if(!visited[w->W(current.position)] && !w->getContent(w->W(current.position))) {
      visitableNeighbors.push_back(AStarNode(w->W(current.position), current.accCost + 1,
        distanceToClosestBorder(w, w->W(current.position))));
      visited[w->W(current.position)] = true;
    }

    for(int i = 0; i < visitableNeighbors.size(); i++) {
      cameFrom[visitableNeighbors[i].position] = current.position;
      frontier.push(visitableNeighbors[i]);
    }

    AStarNode lowestDistance = visitableNeighbors[0];
    for(int i = 0; i < visitableNeighbors.size(); i++) {
      if(visitableNeighbors[i].heuristic < lowestDistance.heuristic) {
        lowestDistance = visitableNeighbors[i];
      }
    }

    current = lowestDistance;
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  if(borderExit != Point2D::INFINITE) {
    vector<Point2D> path;
    path.push_back(borderExit);
    if(cameFrom[borderExit] != catPos) {
      path.push_back(cameFrom[borderExit]);
      Point2D next = cameFrom[borderExit];
      while(cameFrom[next] != catPos) {
        next = cameFrom[next];
        path.push_back(next);
      }
    }
    return path;
  }
  return vector<Point2D>();
}
