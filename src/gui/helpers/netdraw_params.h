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
  
  double  o_angle_offset_;    //  
  double  m_angle_offset_;   // offset of circles relative to start_angle_
  double  i_angle_offset_;    //

  bool    o_angle_offset_positive_;
  bool    m_angle_offset_positive_; // helper vars for 3rdparty functions
  bool    i_angle_offset_positive_;
  
  double  o_rad_offset_;      //
  double  m_rad_offset_;     // offset to radius of circles
  double  i_rad_offset_;      //

  bool    o_rad_offset_positive_;
  bool    m_rad_offset_positive_; // helper vars for 3rdparty functions
  bool    i_rad_offset_positive_;

  int     line_type_;
  int     line_width_;
  Color   poly_color_;

  NetdrawParams() 
    : is_draw_poly_{true}
    , is_draw_digits_{true}
    , start_angle_{90}            // value = 90 allows to draws polys north-oriented
    , o_angle_offset_{0}
    , m_angle_offset_{0}
    , i_angle_offset_{0}
    , o_angle_offset_positive_{true}
    , m_angle_offset_positive_{true}
    , i_angle_offset_positive_{true}
    , o_rad_offset_{0}
    , m_rad_offset_{0}
    , i_rad_offset_{0}
    , o_rad_offset_positive_{true}
    , m_rad_offset_positive_{true}
    , i_rad_offset_positive_{true}
    , line_type_{3}
    , line_width_{5}
    , poly_color_{255, 255, 255}  // in RGB - white color
  { }
  // void Reset() { NetdrawParams(); }
};

}  // namespace wumpus_game

#endif  // NETDRAW_PARAMS_H