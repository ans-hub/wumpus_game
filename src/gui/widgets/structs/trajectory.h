// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents movement trajectory on the 2D surface

#ifndef TRAJECTORY_GEO_H
#define TRAJECTORY_GEO_H

#include <vector>
#include "point.h"

namespace wumpus_game {

struct Trajectory
{
  enum Type
  {
    LINE,
    CURVE
  };
  
  std::vector<Point> points_;

  Trajectory() : points_{ } { }  
  bool  Empty() const { return points_.empty(); }
  void  Set(double, double, double, double, Type, int);
  Point Next() const { return points_.back(); }
  void  Pop() { points_.pop_back(); }
  void  Reset() { points_.clear(); points_.resize(0); }
};

namespace draw_helpers {

  Point get_point_on_line(Point, Point, int);
  std::vector<Point> build_line_trajectory(Point&, Point&, int);
  std::vector<Point> build_curve_trajectory(Point&, Point&, int);

}  // namespace draw_helpers
 
}  // namespace wumpus_game

#endif  // TRAJECTORY_GEO_H