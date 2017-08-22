// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: functions set represents current configuration in game 
// usually in depends of given level value

#include "config.h"

namespace wumpus_game {

// AUDIO SETTINGS

std::string config::GetBackgroundMusic(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      return "resources/sounds/theme_cave.wav";

    case 4 : case 5 : case 6 : 
      return "resources/sounds/theme_underwater.mp3";

    case 7  : case 8  : case 9  : case 10 :
      return "resources/sounds/theme_dead_town.ogg";

    case 11 : case 12 : 
      return "resources/sounds/theme_broken_cpu.mp3";

    case 13 :
      return "resources/sounds/theme_last_battle.mp3";

    case 14 : 
      return "resources/sounds/theme_home.mp3";
  }
}

std::string config::GetPlayerSound(PlayerState type, int level)
{
  switch(type) {

    case PlayerState::MOVED_BY_BATS :
      if (level == 4 || level == 5 || level == 6)
        return "resources/sounds/bats_movement_uw.mp3";
      else
        return "resources/sounds/bats_movement.mp3";

    case PlayerState::WALK : 
    if (level == 4 || level == 5 || level == 6)
      return "resources/sounds/player_walk_uw.mp3";
    else
      return "resources/sounds/player_walk.wav";

    case PlayerState::SHOT : 
      if (level == 11 || level == 12) 
        return "resources/sounds/player_shot_bc.mp3";
      else if (level == 13) 
        return "resources/sounds/player_shot_lb.mp3";
      else
        return "resources/sounds/player_shot.wav";

    case PlayerState::KILLED_BY_PITS :
      if (level == 4 || level == 5 || level == 6)
        return "resources/sounds/bats_movement_uw.mp3";
      if (level == 11 || level == 12) 
        return "resources/sounds/player_pits_bc.mp3";
      else      
        return "resources/sounds/player_pits.wav";

    case PlayerState::KILLED_BY_WUMP : 
      return "resources/sounds/wump_attack.wav";

    case PlayerState::KILL_WUMP : 
      if (level == 11 || level == 12) 
        return "resources/sounds/wump_killed_bc.mp3";
      else if (level == 13) {
        return "resources/sounds/player_shot_lb.mp3";
      }
      else if (level == 14)
        return "resources/sounds/wump_killed_hm.wav";
      else 
        return "resources/sounds/wump_killed.wav";

    case PlayerState::HAVENT_ARROWS : 
      return "resources/sounds/click.wav";

    case PlayerState::FEELS_WUMP :
      if (level == 14) 
        return "resources/sounds/wump_feels_hm.wav";
      else
        return "resources/sounds/wump_feels.wav";
    
    case PlayerState::MEETS_CLOSED_GUIDE :
      return "resources/sounds/player_guide_knock.wav";

    case PlayerState::LEVEL_WIN :
      return "resources/sounds/player_win.wav";

    case PlayerState::UNKNOWN_STATE :
      return "resources/sounds/click.wav";
    
    case PlayerState::STAY : default :
      return "resources/sounds/silence.wav";
  }
}

// FORM_MAP SETTINGS

std::string config::GetSceneName(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      return "In the Dark cave";
    
    case 4 : case 5 : case 6 :
      return "Underwater hunt";

    case 7 : case 8 : case 9 : case 10 :
      return "Way to Sweet home";

    case 11 : case 12 :
      return "Broken teleport circuit";

    case 13 :
      return "Last battle";

    case 14 :
      return "Kitty-kitty...";
  }
}

Fl_Color config::GetSceneColor(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      return 40;
    
    case 4 : case 5 : case 6 :
      return 148;

    case 7 : case 8 : case 9 : case 10 :
      return 20;
    
    case 11 : case 12 :
      return 32;
  
    case 13 :
      return 44;
  
    case 14 :
      return 44;    
  }
}


// LOGIC SETTINGS

int config::levels_max = 14;

int config::GetMapBase(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 : 
      return level + 4;
    case 4 : case 5 : case 6 : 
      return level + 1;
    case 7 : case 8 : case 9 : case 10 : 
      return level - 2;
    case 11 : case 12 :
      return level - 6;
    case 13 : 
      return level - 7;
    case 14 : default :
      return level - 10;
  }
}

int config::GetRoomsCount(int level)
{
  using namespace config;

  return (GetMapBase(level) * 4);
}

int config::GetArrowsCount(int level)
{ 
  using namespace config;
  
  switch(level) {
    case 13 :
      return GetRoomsCount(level) - 2;
    case 14 :
      return GetRoomsCount(level) - (GetRoomsCount(level) / 2);   
    default :
      return GetRoomsCount(level) / 4;    
  }
}

int config::GetWumpsCount(int level)
{ 
  using namespace config;

  switch(level) {
    case 13 :
      return GetRoomsCount(level) / 2;
    case 14 :
      return GetRoomsCount(level) - (GetRoomsCount(level) / 2); 
    default :
      return GetRoomsCount(level) / 9;
  }
}

int config::GetBatsCount(int level)
{
  using namespace config;

  switch(level) {
    case 13 : case 14 :
      return 0;
    default :
      return GetRoomsCount(level) / 9;
  }
}

int config::GetPitsCount(int level)
{
  using namespace config;
  
  switch(level) {
    case 13 : case 14 : 
      return 0;
    default :
      return GetRoomsCount(level) / 9;        
  }
}

// WIDGET_NETDRAW SETTINGS

double config::edge_len = 12;

int config::room_btn_size = 30;

int config::main_wnd_offset = 30;

double config::netdraw_start_angle = 90;

// Returns min width of screen needs to place WidgetNetdraw in depends of level

double config::GetLevelWidth(int)
{
  return GetRoomsCount(2) * edge_len * 2;
}

// WIDGET_MAP SETTINGS

// Pixels count to every animation player tick

int config::animation_step = 5; 

double config::GetPlayerAnimationSpeed(int level)
{
  switch(level) {
    case 11 : case 12 :
      return 0.02;
    case 13 : 
      return 0.01;
    case 14 :
      return 0.04;
    default :
      return 0.03;
  }
}

// Pixels count to every animation rotate map tick

double config::GetRotateMapStep(int)
{
  return 0.3;
}

double config::GetRotateMapSpeed(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 :
      return 0;
    case 4 : 
      return 0.05;
    case 5 : case 6 : 
      return 0.03;
    case 7 :
      return 0.06;
    case 8 : 
      return 0.05;
    case 9 : case 10 :
      return 0.02;
    case 11 : case 12 :
      return 1.0;
    case 13 :
      return 0.015;
    case 14 :
      return 0.03;
    default :
      return 0;
  }
}

// Returns true if widget_map should mark rooms after its visiting

bool config::WhetherToMarkVisitedRooms(int level)
{
  switch(level) {
    case 7 : case 8 : case 9: case 10 : case 14 : 
      return true;
    default : 
      return false;
  }
}

// Changes NetdrawParams& object (used by WidgetNetdraw) in depends of level
// Called in every `rotate_map_step` seconds from WidgetMap to emulate rotating
// of WidgetNetdraw

void config::ChangeNetdrawParams(NetdrawParams& params, int level)
{
  auto step = config::GetRotateMapStep(level);

  switch (level) {

    case 3 : case 4 : case 5 :
      params.start_angle_ += step;
      break;

    case 6 :
      params.start_angle_ += step;
      cfg_helpers::ChangeMiddleRadius(params, step, step*2, 20.0);
      break;

    case 7 :
      params.start_angle_ += step;
      cfg_helpers::ChangeMiddleAngle(params, step, step*2, 30.0);    
      break;
    case 8 : 
      params.start_angle_ += step;
      params.m_angle_offset_ += step;
      break;

    case 9 : 
      params.start_angle_ += step;    
      params.m_angle_offset_ += -(step*2);
      cfg_helpers::ChangeMiddleRadius(params, step, step*2, 20.0);
      break;

    case 10 :
      params.m_rad_offset_ = 0;
      params.start_angle_ += step;      
      params.m_angle_offset_ += -(step*2);      
      break;

    case 11 :
      cfg_helpers::ChangeAllDoublesRandom(params);
      params.is_draw_digits_ = !params.is_draw_digits_;
      params.is_draw_poly_ = false;
      break;

    case 12 :
      cfg_helpers::ChangeAllDoublesRandom(params);
      params.is_draw_digits_ = !params.is_draw_digits_;
      params.is_draw_poly_ = false;
      break;
      
    case 13 :
      params.start_angle_ += step * 2;      
      params.m_angle_offset_ += -(step*4);            
      cfg_helpers::ChangeMiddleRadius(params, step, step*2, 10.0);
      cfg_helpers::ChangeOuterRadius(params, step, step*2, 10.0);
      params.is_draw_digits_ = true;
      params.is_draw_poly_ = true;
      break;

    case 14 :
      params.start_angle_ = 0;
      params.m_angle_offset_ = 0;
      params.o_rad_offset_ = 80;
      params.is_m_is_circle_ = true;
      params.line_type_ = 0;
      params.line_width_ = 2;
      cfg_helpers::ChangeMiddleRadius(params, step, step, 20);
      break;
      
    default :
      params = NetdrawParams();
  }
}

// HELPERS

// Changes angle offset of middle circle in Netdraw by range (+/-)
// step_f - step forward, step_b - step back. Sometimes its useful to 
// make step_b in double size, since some levels rotate total_angle forward

void cfg_helpers::ChangeMiddleAngle(
  NetdrawParams& params, double step_f, double step_b, double range)
{
  if (params.m_angle_offset_ > (step_f * range))
    params.m_angle_offset_positive_ = false;
  else if (params.m_angle_offset_ < -(step_b * range)) 
    params.m_angle_offset_positive_ = true;

  if (params.m_angle_offset_positive_)
    params.m_angle_offset_ += step_f;
  else
    params.m_angle_offset_ -= step_b;
}

// Changes radius offset of middle circle in Netdraw by range (+/-)

void cfg_helpers::ChangeMiddleRadius(
  NetdrawParams& params, double step_f, double step_b, double range)
{
  if (params.m_rad_offset_ > (step_f * range)) 
    params.m_rad_offset_positive_ = false;
  else if (params.m_rad_offset_ < -(step_b * range))
    params.m_rad_offset_positive_ = true;

  if (params.m_rad_offset_positive_)
    params.m_rad_offset_ += step_f;
  else 
    params.m_rad_offset_ -= step_b;
}

// Changes radius offset of middle circle in Netdraw by range (+/-)

void cfg_helpers::ChangeOuterRadius(
  NetdrawParams& params, double step_f, double step_b, double range)
{
  if (params.o_rad_offset_ > (step_f * range)) 
    params.o_rad_offset_positive_ = false;
  else if (params.o_rad_offset_ < -(step_b * range))
    params.o_rad_offset_positive_ = true;

  if (params.o_rad_offset_positive_)
    params.o_rad_offset_ += step_f;
  else 
    params.o_rad_offset_ -= step_b;
}

// Changes all parametrs contains doubles values in random order

void cfg_helpers::ChangeAllDoublesRandom(NetdrawParams& params)
{    
  params = NetdrawParams();
  double step = rand_toolkit::get_rand(0,10);

  if (rand_toolkit::coin_toss())
    params.start_angle_ += step;
  else
    params.start_angle_ -= step;

  if (rand_toolkit::coin_toss())          
    params.m_angle_offset_ -= step * 2;
  else 
    params.m_angle_offset_ += step * 2; 

  if (rand_toolkit::coin_toss())
    params.o_rad_offset_ -= step;
  else 
    params.o_rad_offset_ -= step;      

  if (rand_toolkit::coin_toss())
    params.m_rad_offset_ -= step;
  else 
    params.m_rad_offset_ -= step;      

  if (rand_toolkit::coin_toss())
    params.i_rad_offset_ -= step;
  else 
    params.i_rad_offset_ -= step;  
}

}  // namespace wumpus_game