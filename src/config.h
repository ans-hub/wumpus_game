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

#include "enums/enums.h"
#include "gui/helpers/netdraw_params.h"

namespace wumpus_game {

namespace config {

  // Audio settings

  std::string     GetBgMusic(int level = 1);
  std::string     GetPlayerSound(PlayerState, int level = 1);
  
  // Gui settings

  // std::string     GetBgImage(int level);

  // Widget_netdraw settings
  
  extern double   edge_len;
  extern int      room_btn_size; 
  extern int      main_wnd_offset;
  extern double   netdraw_start_angle;
  void            ChangeNetdrawParams(NetdrawParams&, int level);

  double          pi();
  int             GetVertexesCount(int level);
  double          GetLevelWidth(int level);

  // Widget_map settings

  double          rotate_map_speed(int level);
  extern double   rotate_map_step;
  double GetPlayerAnimationSpeed(int level);
  extern int      animation_step;
  
  // Logic settings 

  extern int      levels_max;
  int             MapBase(int level);
  int             RoomsCount(int level);
  int             ArrowsCount(int level);
  int             WumpsCount(int level);
  int             BatsCount(int level);
  int             PitsCount(int level);
  
}  // namespace conf

namespace helpers {

  void ChangeTotalAngle(NetdrawParams&, double);

  void ChangeMiddleAngle(NetdrawParams&, double);             // + step
  void ChangeMiddleAngle(NetdrawParams&, double, double);     // + range
  
  void ChangeMiddleRadius(NetdrawParams&, double);            // ???
  void ChangeMiddleRadius(NetdrawParams&, double, double);

  void ChangeOuterRadius(NetdrawParams&, double, double);

  void ChangeAllDoublesRandom(NetdrawParams&);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // GAME_CONFIG_H