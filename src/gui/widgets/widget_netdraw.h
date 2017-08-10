// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget draws pathes between rooms

#ifndef WIDGET_NETDRAW_H
#define WIDGET_NETDRAW_H

#include <vector>
#include <sstream>
#include <cmath>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include "gui/helpers/point.h"
#include "settings/config.h"

namespace wumpus_game {

struct WidgetNetdraw : public Fl_Widget
{
  using VPoint = std::vector<Point>;
  using cVPoint = const VPoint;
  
  explicit WidgetNetdraw(int);
  WidgetNetdraw(int, double);
  virtual ~WidgetNetdraw() { }
  
  void      Redraw(int);
  cVPoint&  GetVertexes() const { return total_vxs_; }

  // Functions to set and get draw distances and angles for net

  void      SetStartAngle(double a) { start_angle_ = a; }
  double    GetStartAngle() const { return start_angle_; }
  void      SetOuterAngleOffset(double a) { outer_angle_offset_ = a; }
  void      SetMiddleAngleOffset(double a) { middle_angle_offset_ = a; }
  void      SetInnerAngleOffset(double a) { inner_angle_offset_ = a; }
  double    GetOuterAngleOffset() const { return outer_angle_offset_; }
  double    GetMiddleAngleOffset() const { return middle_angle_offset_; }
  double    GetInnerAngleOffset() const { return inner_angle_offset_; }
  void      ResetAnglesToDefault();

private:

  // Default values of net

  constexpr static double kStartAngle = 90;
  constexpr static double kOuterAngleOffset = 0;
  constexpr static double kMiddleAngleOffset = 0;
  constexpr static double kInnerAngleOffset = 0;
  
  int     vxs_count_;
  VPoint  total_vxs_;            // all coords of all circles
  VPoint  inner_vxs_;            //
  VPoint  middle_vxs_;           // coords of vertexes relative to concrete circle
  VPoint  outer_vxs_;            //
  double  start_angle_;          // angle from which starts calc coordinates of circles
  double  outer_angle_offset_;   //  
  double  middle_angle_offset_;  // offset of circles relative to start_angle_
  double  inner_angle_offset_;   //

  void FillAllVertexes();
  void draw() override;
};

namespace draw_helpers {

  using PointVec = std::vector<Point>;

  PointVec get_poly_vertexes(double, double, double, double, double);
  bool fill_vector_by_another(PointVec&, const PointVec&, double, double);
  void draw_points(const PointVec&, WidgetNetdraw*, int);
  void draw_poly(const PointVec&, WidgetNetdraw*);
  void draw_edges(const PointVec&, WidgetNetdraw*);

}  // namespace draw_helpers

}  // namespace wumpus_game

#endif  // WIDGET_NETDRAW_H