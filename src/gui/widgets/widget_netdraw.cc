// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget draws pathes between rooms
//
// Note : This widget draws net, in other words presents a view of net,
// generated by "entities/map.h". To see more information about inner,
// middle and outer vertexes and other special terms, you shall read
// "entities/map.cc" annotation in the top of the file

#include "widget_netdraw.h"

namespace wumpus_game {

WidgetNetdraw::WidgetNetdraw()
  : Fl_Widget(0,0,0,0)
  , params_{}
  , vxs_count_{}
  , total_vxs_{}
  , inner_vxs_{}
  , middle_vxs_{}
  , outer_vxs_{}
  , center_{} { }

WidgetNetdraw::WidgetNetdraw(double start_angle)
  : WidgetNetdraw()
{
  params_.start_angle_ = start_angle;
}

void WidgetNetdraw::Redraw(int level)
{
  vxs_count_ = config::GetRoomsCount(level);
  total_vxs_.resize(vxs_count_);

  int w = config::GetLevelWidth(level);
  resize(0, 0, w, w);

  FillAllVertexes();
}

void WidgetNetdraw::FillAllVertexes()
{
  // Prepare

  double width = w();
  double height = h();
  center_.x_ = width/2;
  center_.y_ = height/2;

  // Get points of inner polygon 

  double ivxs_count_ = vxs_count_/4;
  double irad = (width / 6) + params_.i_rad_offset_;
  double istart_angle = params_.start_angle_ + params_.i_angle_offset_;

  inner_vxs_ = wdg_helpers::GetPolyVertexes(
    ivxs_count_, irad, istart_angle, center_.x_, center_.y_
  );
  
  // Get points of middle polygon

  double mvxs_count_ = vxs_count_/2;
  double mrad = (irad * 2) - (width / 20) + params_.m_rad_offset_;
  double mstart_angle = params_.start_angle_ + params_.m_angle_offset_;

  middle_vxs_ = wdg_helpers::GetPolyVertexes(
    mvxs_count_, mrad, mstart_angle, center_.x_, center_.y_
  );
  
  // Get points of outer polygon

  double ovxs_count_ = vxs_count_/4;
  double orad = (width / 2) - (width / 20) + params_.o_rad_offset_;
  double ostart_angle = 
    params_.start_angle_ + (360 / ovxs_count_ / 2) + params_.o_angle_offset_;

  outer_vxs_ = wdg_helpers::GetPolyVertexes(
    ovxs_count_, orad, ostart_angle, center_.x_, center_.y_
  );

  // Fill total map vector by previously recieved polygons points

  double step = 2;
  double start_ivx = vxs_count_/2;
  wdg_helpers::FillVectorByAnother(
    total_vxs_, inner_vxs_, start_ivx, step
  );

  step = 1;
  double start_mvx = 0;
  wdg_helpers::FillVectorByAnother(
    total_vxs_, middle_vxs_, start_mvx, step
  );

  step = 2;
  double start_ovx = (vxs_count_/2)+1;
  wdg_helpers::FillVectorByAnother(
    total_vxs_, outer_vxs_, start_ovx, step
  );
}

void WidgetNetdraw::draw()
{
  if (params_.is_draw_poly_) {
    wdg_helpers::DrawPoly(inner_vxs_, this);
    wdg_helpers::DrawPoly(outer_vxs_, this);
    wdg_helpers::DrawEdges(total_vxs_, this);
    
    if (params_.is_m_is_circle_) {
      double rad = math_helpers::EvalVectorLength(center_, middle_vxs_[0]);
      wdg_helpers::DrawCircle(center_, rad, this);
    } 
    else {
      wdg_helpers::DrawPoly(middle_vxs_, this);
    }
  }

  if (params_.is_draw_digits_) {
    wdg_helpers::DrawDigits(total_vxs_, this);
  }
}

// Function that not need to be member of WidgetNetdraw, but may be used only this
// version of netdraw, since draw logic of net with 3 edges is depends

namespace wdg_helpers {

VPoints GetPolyVertexes(
  double edges, double rad, double angle_start, double x0, double y0)
{
  std::vector<Point> res (edges);
  double angle_step = 360 / edges;
  double angle = angle_start;

  for (double i = 0; i < edges; ++i) {
    if (angle > 360) angle = angle - 360;
    Point p;
    p.x_ = cos(angle * math_helpers::GetPi() / 180) * rad + x0;
    p.y_ = sin(angle * math_helpers::GetPi() / 180) * rad + y0;
    res[i] = p;
    angle += angle_step;
  }
  return res;
}

bool FillVectorByAnother(
  VPoints& res, const VPoints& v, double start, double step)
{
  if (res.size() < v.size())
    return false;
  
  double i = start;
  for (auto v0 : v) {
    res[i] = v0;
    i += step;
  }

  return true;
}

void DrawPoints(const VPoints& v, WidgetNetdraw*, int)
{
  for (const auto& v0 : v) {
    fl_line_style(1,5);
    fl_color(FL_WHITE);
    fl_point(v0.x_, v0.y_);
  }
  fl_line_style(0,1);
}

void DrawPoly(const VPoints& v, WidgetNetdraw* surface)
{
  const auto& params = surface->GetParamsReference();

  fl_color(
    std::get<0>(params.poly_color_),
    std::get<1>(params.poly_color_),
    std::get<2>(params.poly_color_)
  );
  fl_line_style(params.line_type_, params.line_width_);

  for (std::size_t i = 0; i < v.size(); ++i) {
    auto p1 = v[i];
    auto p2 = v[0];
    if (i+1 != v.size()) {
      p2 = v[i+1];
    }
    fl_line(
      surface->x() + p1.x_, surface->y() + p1.y_,
      surface->x() + p2.x_, surface->y() + p2.y_
    );
  }
  fl_line_style(0,1);
}

void DrawCircle(const Point& p, double radius, WidgetNetdraw* surface)
{
  const auto& param = surface->GetParamsReference();

  fl_color(
    std::get<0>(param.poly_color_),
    std::get<1>(param.poly_color_),
    std::get<2>(param.poly_color_)
  );
  fl_line_style(param.line_type_, param.line_width_);

  fl_circle(
    surface->x() + p.x_, surface->y() + p.y_, radius);  
}

void DrawEdges(const VPoints& v, WidgetNetdraw* surface)
{
  const auto& param = surface->GetParamsReference();
  
  double half = static_cast<int>(v.size()/2);

  for (int i = 0; i < half; ++i) {
    auto p1 = v[i];
    auto p2 = v[i+half];

    fl_color(
      std::get<0>(param.poly_color_),
      std::get<1>(param.poly_color_),
      std::get<2>(param.poly_color_)
    );
    fl_line_style(param.line_type_, param.line_width_);
  
    fl_line(
      surface->x() + p1.x_, surface->y() + p1.y_,
      surface->x() + p2.x_, surface->y() + p2.y_
    );
    fl_line_style(0,1);
  }
}

void DrawDigits(const VPoints& v, WidgetNetdraw* surface)
{
  double half = static_cast<int>(v.size()/2);

  for (int i = 0; i < half; ++i) {
    auto p1 = v[i];
    auto p2 = v[i+half];
    
    std::ostringstream s1{};
    std::ostringstream s2{};
    s1 << i;
    s2 << i+half;  

    fl_color(Fl_Color(99));
    fl_font(fl_font(),14);
    fl_draw(
      s1.str().c_str(),
      surface->x() + p1.x_ + 20,
      surface->y() + p1.y_ + 20
    );
    fl_draw(
      s2.str().c_str(),
      surface->x() + p2.x_ + 20,
      surface->y() + p2.y_ + 20
    );
  }
}

}  // namespace wdg_helpers

}  // namespace wumpus_game