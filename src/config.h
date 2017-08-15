// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: functions set represents current configuration in game 
// usually in depends of given level value

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

  std::string   GetBackgroundMusic(int level = 1);
  std::string   GetPlayerSound(PlayerState, int level = 1);

  // Logic settings 

  extern int    levels_max;
  int           GetMapBase(int level);
  int           GetRoomsCount(int level);
  int           GetArrowsCount(int level);
  int           GetWumpsCount(int level);
  int           GetBatsCount(int level);
  int           GetPitsCount(int level);
  
  // Widget_netdraw.h settings
  
  extern double edge_len;           // see terms inside widget_netdraw.h
  extern int    room_btn_size; 
  extern int    main_wnd_offset;
  extern double netdraw_start_angle;
  double        GetLevelWidth(int level);

  // Widget_map settings

  extern int    animation_step;
  double        GetPlayerAnimationSpeed(int level);
  extern double rotate_map_step;
  double        GetRotateMapSpeed(int level);
  bool          WhetherToMarkVisitedRooms(int level);
  void          ChangeNetdrawParams(NetdrawParams&, int level);
  
}  // namespace conf

namespace helpers {

  void ChangeTotalAngle(NetdrawParams&, double);

  void ChangeMiddleAngle(NetdrawParams&, double);             // + step
  void ChangeMiddleAngle(NetdrawParams&, double, double, double);     // + range
  
  void ChangeMiddleRadius(NetdrawParams&, double);            // ???
  void ChangeMiddleRadius(NetdrawParams&, double, double, double);
  
  void ChangeOuterRadius(NetdrawParams&, double);
  void ChangeOuterRadius(NetdrawParams&, double, double, double);

  void ChangeAllDoublesRandom(NetdrawParams&);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // GAME_CONFIG_H