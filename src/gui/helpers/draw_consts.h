// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: constants and rules for window drawings

#ifndef DRAW_CONSTS_H
#define DRAW_CONSTS_H

#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Text_Buffer.H>

namespace wumpus_game {

namespace draw_consts {
  
  constexpr double  pi() { return std::atan(1)*4; }
  
  constexpr double  edge_len = 12;
  constexpr int     room_btn_size = 30;
  constexpr int     main_wnd_offset = 30;
  constexpr int     animation_step = 1;
  constexpr double  animation_speed =  0.012;

  int     level_vertexes(int);
  double  level_width(int); 

}  // namespace draw_consts

}  // namespace wumpus_game

#endif  //DRAW_CONSTS_H