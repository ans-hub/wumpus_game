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
      points_ = draw_helpers::build_line_trajectory(from, to, step);
      break;
    case CURVE :
      points_ = draw_helpers::build_bezier_trajectory(from, to, step);
      break;
    default : break;
  }
}

namespace draw_helpers {

// Define vector coordinates

Point eval_vector_coordinates(const Point& a, const Point& b)
{
  return {b.x_-a.x_, b.y_-a.y_};
}

// Define vector length

double eval_vector_length(const Point& a, const Point& b)
{
  auto v = eval_vector_coordinates(a,b);
  return std::sqrt(v.x_*v.x_ + v.y_*v.y_);
}

// Get point lies on the vector

Point get_point_on_vector(const Point& a, const Point& b, double part)
{
  return a + part*(b-a);
}

// Fill vector with points lies on the line in reversed order
// without coord which is `from`

std::vector<Point> build_line_trajectory(const Point& from, const Point& to, int step)
{
  double len = eval_vector_length(from, to);
  int steps = len/step;

  std::vector<Point> v(steps+1);   // since 1 step consists of 2 points

  for (int i = 0; i < steps; ++i) {
    double part = (double)i/steps;
    Point p = draw_helpers::get_point_on_vector(from, to, part);
    v[steps-i] = p;
  }
  v[0] = to;
  if (v.size() != 1) v.pop_back();   // remove current from coord

  return v;
}

// Fill vector with points lies on the curve in reversed order
// https://learn.javascript.ru/bezier

std::vector<Point> build_bezier_trajectory(const Point& from, const Point& to, int step)
{
  double len = eval_vector_length(from, to);
  int steps = len/step;

  
  std::vector<Point> v(steps+1);

  return v;
}

}  // namespace draw_helpers

}  // namespace wumpus_game