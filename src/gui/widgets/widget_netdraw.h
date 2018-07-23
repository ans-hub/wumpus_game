// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget draws pathes between rooms

#ifndef WIDGET_NETDRAW_H
#define WIDGET_NETDRAW_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include "gui/helpers/point.h"
#include "gui/helpers/netdraw_params.h"
#include "gui/helpers/math_helpers.h"
#include "config.h"

namespace wumpus_game {

class WidgetNetdraw : public Fl_Widget
{
public:
  using VPoints = std::vector<Point>;
  using cVPoints = const VPoints;
  using Params = NetdrawParams;

  WidgetNetdraw();
  explicit WidgetNetdraw(double);
  virtual ~WidgetNetdraw() { }
  
  void      Redraw(int);
  Params&   GetParamsReference() { return params_; }
  cVPoints& GetVertexes() const { return total_vxs_; }

private:
  Params    params_;        // changable drawing parametrs
  int       vxs_count_;     // total vertexes count  
  VPoints   total_vxs_;     // contains coords of all vertexes of net

  VPoints   inner_vxs_;     //
  VPoints   middle_vxs_;    // coords of vertexes relative to concrete circle
  VPoints   outer_vxs_;     //
  
  Point     center_;
  
  void FillAllVertices();
  void draw() override;
};

namespace wdg_helpers {

  using VPoints = std::vector<Point>;

  VPoints GetPolyVertices(double, double, double, double, double);
  bool    FillVectorByAnother(VPoints&, const VPoints&, double, double);
  void    DrawPoints(const VPoints&, WidgetNetdraw*, int);
  void    DrawPoly(const VPoints&, WidgetNetdraw*);
  void    DrawCircle(const Point&, double, WidgetNetdraw*);
  void    DrawEdges(const VPoints&, WidgetNetdraw*);
  void    DrawDigits(const VPoints&, WidgetNetdraw*);
  
}  // namespace wdg_helpers

}  // namespace wumpus_game

#endif  // WIDGET_NETDRAW_H