// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: helper struct represents parameters of draw net in WidgetNetdraw

#ifndef NETDRAW_PARAMS_H
#define NETDRAW_PARAMS_H

#include <tuple>

namespace wumpus_game {

// Configuration structure to WidgetNetdraw

struct NetdrawParams
{
  using Color = std::tuple<char, char, char>;

  bool    is_draw_poly_;
  bool    is_draw_digits_;

  double  start_angle_;           // angle from which starts calc coordinates of circles
  
  double  outer_angle_offset_;    //  
  double  middle_angle_offset_;   // offset of circles relative to start_angle_
  double  inner_angle_offset_;    //
  
  double  outer_rad_offset_;      //
  double  middle_rad_offset_;     // offset to radius of circles
  double  inner_rad_offset_;      //

  int     line_type_;
  int     line_width_;
  Color   poly_color_;

  NetdrawParams() 
    : is_draw_poly_{true}
    , is_draw_digits_{true}
    , start_angle_{90}            // value = 90 allows to draws polys north-oriented
    , outer_angle_offset_{0}
    , middle_angle_offset_{0}
    , inner_angle_offset_{0}
    , outer_rad_offset_{0}
    , middle_rad_offset_{0}
    , inner_rad_offset_{0}
    , line_type_{3}
    , line_width_{5}
    , poly_color_{255, 255, 255}  // in RGB - white color
  { }
  void Reset() { NetdrawParams(); }
};

}  // namespace wumpus_game

#endif  // NETDRAW_PARAMS_H