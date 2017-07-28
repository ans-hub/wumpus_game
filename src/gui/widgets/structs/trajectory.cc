// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents movement trajectory on the 2D surface

#include "trajectory.h"

namespace wumpus_game {

void Trajectory::Set(
  double from_x, double from_y, double to_x, double to_y, Type t, int step)
{
  Point from {from_x, from_y};
  Point to {to_x, to_y};

  switch(t) {
    case LINE :
      points_ = draw_helpers::build_line_trajectory(from, to, step);
      break;
    case CURVE :
      points_ = draw_helpers::build_curve_trajectory(from, to, step);
      break;
    default : break;
  }
}

namespace draw_helpers {

// Get point lies on the line

Point get_point_on_line(const Point& a, const Point& b, double part)
{
  return a + part*(b-a);
}

// Fill vector with points lies on the line in reversed order

std::vector<Point> build_line_trajectory(Point& from, Point& to, int step)
{
  std::vector<Point> v(step);

  for (int i = 0; i < step; ++i) {
    double part = (double)i/step;
    Point p = draw_helpers::get_point_on_line(from, to, part);
    v[step-i-1] = p;
  }
  return v;
}

// Fill vector with points lies on the curve in reversed order

std::vector<Point> build_curve_trajectory(Point&, Point&, int)
{
  std::vector<Point> v(0);
  return v;
}

}  // namespace draw_helpers

}  // namespace wumpus_game