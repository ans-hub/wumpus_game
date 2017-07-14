// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: FLTK widget draw pathes between rooms

#ifndef MAP_PATHES_H
#define MAP_PATHES_H

#include <vector>
#include <sstream>
#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include "../helpers/draw_consts.h"

namespace wumpus_game {

struct Point
{
  double x_;
  double y_;
};

struct MapPathes : public Fl_Widget
{
  using PointVec = std::vector<Point>;
  using cPointVec = const PointVec;
  
  MapPathes(int);
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
  void draw_points(const PointVec&, MapPathes*, int);
  void draw_poly(const PointVec&, MapPathes*);
  void draw_edges(const PointVec&, MapPathes*);

}  // namespace draw_helpers

}  // namespace wumpus_game

#endif  // MAP_PATHES_H