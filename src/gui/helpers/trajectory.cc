// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents movement trajectory on the 2D surface

#include "trajectory.h"

namespace wumpus_game {

void Trajectory::Set(const Point& from, const Point& to, Type t, int step)
{
  switch(t) {
    case LINE :
      points_ = math_helpers::BuildLineTrajectory(from, to, step);
      break;
    case CURVE :
      points_ = math_helpers::BuildBezierTrajectory(from, to, step);
      break;
    default : break;
  }
}

}  // namespace wumpus_game