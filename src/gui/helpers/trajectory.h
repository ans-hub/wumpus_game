// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents movement trajectory on the 2D surface

#ifndef TRAJECTORY_GEO_H
#define TRAJECTORY_GEO_H

#include <vector>
#include <cmath>

#include "gui/helpers/point.h"
#include "gui/helpers/math_helpers.h"

namespace wumpus_game {

struct Trajectory
{
  enum Type
  {
    LINE,
    CURVE
  };
  
  Trajectory() : points_{ } { }
  void  Set(const Point&, const Point&, Type, int);
  Point Next() const { return points_.back(); }
  Point First() const { return points_[0]; }
  void  Reset() { points_.clear(); points_.resize(0); }
  void  Pop() { points_.pop_back(); }
  bool  Empty() const { return points_.empty(); }

private:
  std::vector<Point> points_;
};

}  // namespace wumpus_game

#endif  // TRAJECTORY_GEO_H