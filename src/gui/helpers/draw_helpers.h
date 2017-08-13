// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helpers that perform vector calculations

#ifndef DRAW_HELPERS_H
#define DRAW_HELPERS_H

#include <vector>
#include <cmath>

#include "gui/helpers/point.h"

namespace wumpus_game {

namespace draw_helpers {

  Point eval_vector_coordinates(const Point&, const Point&);
  double eval_vector_length(const Point&, const Point&);
  Point get_point_on_vector(const Point&, const Point&, int);
  std::vector<Point> build_line_trajectory(const Point&, const Point&, int);
  std::vector<Point> build_bezier_trajectory(const Point&, const Point&, int);

}  // namespace draw_helpers
 
}  // namespace wumpus_game

#endif  // DRAW_HELPERS_H