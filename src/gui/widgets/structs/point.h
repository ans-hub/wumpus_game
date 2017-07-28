// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents Point on the 2D surface

#ifndef POINT_GEO_H
#define POINT_GEO_H

namespace wumpus_game {

struct Point
{
  double x_;
  double y_;

  Point() : x_{0}, y_{0} { }
  Point(double x, double y) : x_{x}, y_{y} { }
  
  friend Point operator+(const Point& lhs, const Point& rhs)
  {
    Point res{};
    res.x_ = lhs.x_ + rhs.x_;
    res.y_ = lhs.y_ + rhs.y_;
    return res;
  }

  friend Point operator-(const Point& lhs, const Point& rhs)
  {
    Point res{};
    res.x_ = lhs.x_ - rhs.x_;
    res.y_ = lhs.y_ - rhs.y_;
    return res;
  }

  friend Point operator*(double num, const Point& lhs)
  {
    Point res{};
    res.x_ = lhs.x_ * num;
    res.y_ = lhs.y_ * num;
    return res;
  }
};

}  // namespace wumpus_game

#endif  // POINT_GEO_H