#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  int distanceToClosestBorder(World* w, Point2D catPos);

  std::vector<Point2D> generatePath(World* w);

  struct AStarNode {
    Point2D position;
    int accCost;
    int heuristic;
    //AStarNode* cameFrom;

    bool operator < (const AStarNode& rhs) const {
      return (accCost + heuristic) > (rhs.accCost + rhs.heuristic);
    }
  };
};

#endif  // AGENT_H
