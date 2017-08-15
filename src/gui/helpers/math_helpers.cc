// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helpers that perform calculations from linear algebra and other

#include "math_helpers.h"

namespace wumpus_game {

// Returns Pi

double math_helpers::GetPi()
{
  return std::atan(1)*4;
}

// Define vector coordinates

Point math_helpers::EvalVectorCoordinates(const Point& a, const Point& b)
{
  return {b.x_-a.x_, b.y_-a.y_};
}

// Define vector length

double math_helpers::EvalVectorLength(const Point& a, const Point& b)
{
  auto v = EvalVectorCoordinates(a,b);
  return std::sqrt(v.x_*v.x_ + v.y_*v.y_);
}

// Get point lies on the vector

Point math_helpers::GetPointOnVector(const Point& a, const Point& b, double part)
{
  return a + part*(b-a);
}

// Fill vector with points lies on the line in reversed order
// without coord which is `from`

std::vector<Point> math_helpers::BuildLineTrajectory(
  const Point& from, const Point& to, int step)
{
  double len = EvalVectorLength(from, to);
  int steps = len/step;

  std::vector<Point> v(steps+1);   // since 1 step consists of 2 points

  for (int i = 0; i < steps; ++i) {
    double part = (double)i/steps;
    Point p = GetPointOnVector(from, to, part);
    v[steps-i] = p;
  }
  v[0] = to;
  if (v.size() != 1) v.pop_back();   // remove current from coord

  return v;
}

// Fill vector with points lies on the curve in reversed order
// https://learn.javascript.ru/bezier

std::vector<Point> math_helpers::BuildBezierTrajectory(
  const Point& from, const Point& to, int step)
{
  double len = EvalVectorLength(from, to);
  int steps = len/step;

  
  std::vector<Point> v(steps+1);

  return v;
}

}  // namespace wumpus_game