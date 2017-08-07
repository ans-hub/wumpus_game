// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents Point on the 2D surface

#ifndef POINT_GEO_H
#define POINT_GEO_H

#include <cmath>

namespace wumpus_game {

struct Point
{
  int x_;
  int y_;

  Point() : x_{0}, y_{0} { }
  Point(int x, int y) : x_{x}, y_{y} { }
  
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
    res.x_ = std::round(lhs.x_ * num);
    res.y_ = std::round(lhs.y_ * num);
    return res;
  }

  friend bool operator==(const Point& lhs, const Point& rhs)
  {
    if ((lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_)) 
      return true;
    else
      return false;
  }

  friend bool operator!=(const Point& lhs, const Point& rhs)
  {
    return !(lhs == rhs);
  }
};

}  // namespace wumpus_game

#endif  // POINT_GEO_H