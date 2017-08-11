// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents current configuration in game

// This file represents functions, which returns parametrs depends
// on given level value 

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include <cmath>

#include "3rdparty/rand_toolkit.h"

#include "settings/enums.h"
#include "gui/helpers/netdraw_params.h"

namespace wumpus_game {

namespace config {

  // Audio settings

  std::string     GetBgMusic(int level);
  std::string     GetSound(PlayerState);
  
  // Gui settings

  std::string     GetBgImage(int level);

  // Widget_netdraw settings
  
  extern double   edge_len;
  extern int      room_btn_size; 
  extern int      main_wnd_offset;
  extern double   netdraw_start_angle;
  void            ChangeNetdrawParams(NetdrawParams&, int level);

  double          pi();
  int             level_vertexes(int);
  double          level_width(int);

  // Widget_map settings

  double          rotate_map_speed(int);
  extern double   rotate_map_step;
  extern double   animation_speed;      // anim who?? explain
  extern int      animation_step;
  
  // Logic settings 

  extern int      levels_max;
  int             map_base(int level);
  int             rooms_cnt(int level);
  int             arrows_cnt(int level);
  int             wumps_cnt(int level);
  int             bats_cnt(int level);
  int             pits_cnt(int level);
  
}  // namespace conf

}  // namespace wumpus_game

#endif  // GAME_CONFIG_H