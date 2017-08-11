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

#include "gui/helpers/netdraw_params.h"
#include "gui/helpers/point.h"
#include "settings/config.h"

namespace wumpus_game {

class WidgetNetdraw : public Fl_Widget
{
public:
  using VPoint = std::vector<Point>;
  using cVPoint = const VPoint;
  using Params = NetdrawParams;

  WidgetNetdraw();
  explicit WidgetNetdraw(double);
  virtual ~WidgetNetdraw() { }
  
  Params&   GetParamsReference() { return params_; }
  void      Redraw(int);
  cVPoint&  GetVertexes() const { return total_vxs_; }
  void      ResetDrawParamsToDefault() { params_ = NetdrawParams(); }

private:
  Params    params_;
  int       vxs_count_;            // total vertexes count  
  VPoint    total_vxs_;            // all coords of all circles
  VPoint    inner_vxs_;            //
  VPoint    middle_vxs_;           // coords of vertexes relative to concrete circle
  VPoint    outer_vxs_;            //
  
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
  void draw_digits(const PointVec&, WidgetNetdraw*);
  

}  // namespace draw_helpers

}  // namespace wumpus_game

#endif  // WIDGET_NETDRAW_H