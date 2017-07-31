// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget draw pathes between rooms

#ifndef WIDGET_NETDRAW_H
#define WIDGET_NETDRAW_H

#include <vector>
#include <sstream>
#include <cmath>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

#include "gui/helpers/draw_consts.h"
#include "gui/helpers/point.h"

namespace wumpus_game {

struct WidgetNetdraw : public Fl_Group
{
  using PointVec = std::vector<Point>;
  using cPointVec = const PointVec;
  
  WidgetNetdraw(int);
  cPointVec& GetVertexes() const { return total_vxs_; }
private:
  int      vxs_count_;
  // double   edge_length_;
  PointVec total_vxs_;
  PointVec inner_vxs_;
  PointVec middle_vxs_;
  PointVec outer_vxs_;
  
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