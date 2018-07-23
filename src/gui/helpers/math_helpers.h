// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: math helpers

#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

#include <vector>
#include <cmath>

#include "gui/helpers/point.h"

namespace wumpus_game {

namespace math_helpers {

  using VPoints = std::vector<Point>;

  double  GetPi();
  Point   EvalVectorCoordinates(const Point&, const Point&);
  double  EvalVectorLength(const Point&, const Point&);
  Point   GetPointOnVector(const Point&, const Point&, double);
  VPoints BuildLineTrajectory(const Point&, const Point&, int);
  VPoints BuildBezierTrajectory(const Point&, const Point&, int);

}  // namespace math_helpers
 
}  // namespace wumpus_game

#endif  // MATH_HELPERS_H