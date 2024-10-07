#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
#include "../../cmake-build-debug/_deps/sdl2-src/src/render/software/SDL_draw.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    Point2D current = frontier.front();
    frontier.pop();
    frontierSet.erase(current);
    visited[current] = true;
    vector<Point2D> visitableNeighbors;
    int sideSize = w->getWorldSideSize();
    if(ABS(current.x) >= sideSize/2 || ABS(current.y) == sideSize/2) {
      borderExit = current;
      while(!frontier.empty()) {
        frontier.pop();
      }
      break;
    }
    if(!visited[w->NW(current)] && !w->getContent(w->NW(current))) {
      visitableNeighbors.push_back(w->NW(current));
      visited[w->NW(current)] = true;
    }
    if(!visited[w->NE(current)] && !w->getContent(w->NE(current))) {
      visitableNeighbors.push_back(w->NE(current));
      visited[w->NE(current)] = true;
    }
    if(!visited[w->SW(current)] && !w->getContent(w->SW(current))) {
      visitableNeighbors.push_back(w->SW(current));
      visited[w->SW(current)] = true;
    }
    if(!visited[w->SE(current)] && !w->getContent(w->SE(current))) {
      visitableNeighbors.push_back(w->SE(current));
      visited[w->SE(current)] = true;
    }
    if(!visited[w->E(current)] && !w->getContent(w->E(current))) {
      visitableNeighbors.push_back(w->E(current));
      visited[w->E(current)] = true;
    }
    if(!visited[w->W(current)] && !w->getContent(w->W(current))) {
      visitableNeighbors.push_back(w->W(current));
      visited[w->W(current)] = true;
    }

    for(int i = 0; i < visitableNeighbors.size(); i++) {
      cameFrom[visitableNeighbors[i]] = current;
      frontier.push(visitableNeighbors[i]);
      frontierSet.insert(visitableNeighbors[i]);
    }
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