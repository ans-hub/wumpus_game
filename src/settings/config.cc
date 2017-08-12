// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents current configuration in game

#include "config.h"

namespace wumpus_game {

namespace config {

std::string GetBgMusic(int level)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      return "audio/wav/theme_cave.wav";
    case 4 : case 5 : case 6 : 
      return "audio/wav/theme_underwater.mp3";
    case 7  : case 8  : case 9  : case 10 :
      return "audio/wav/theme_dead_town.ogg";
    case 11 : case 12 : 
      return "audio/wav/theme_broken_cpu.mp3";
    case 13 : 
      return "audio/wav/theme_last_battle.mp3";
    case 14 : 
      return "audio/wav/theme_home.mp3";
  }
}

std::string GetPlayerSound(PlayerState type, int level)
{
  switch(type) {
    case PlayerState::MOVED_BY_BATS : 
      return "audio/wav/bats_movement.wav";
    case PlayerState::WALK : 
      return "audio/wav/player_walk.wav";
    case PlayerState::SHOT : 
      return "audio/wav/player_shot.wav";
    case PlayerState::KILLED_BY_PITS :
      return "audio/wav/player_pits.wav";
    case PlayerState::KILLED_BY_WUMP : 
      return "audio/wav/wump_attack.wav";
    case PlayerState::KILL_WUMP : 
      return "audio/wav/wump_killed.wav";
    case PlayerState::HAVENT_ARROWS : 
      return "audio/wav/click.wav";
    case PlayerState::FEELS_WUMP : 
      return "audio/wav/wump_feels.wav";
    case PlayerState::UNKNOWN_STATE : default : 
      return "audio/wav/click.wav";
  }
}

// GUI SETTINGS

double  edge_len = 12;
int     room_btn_size = 30;
int     main_wnd_offset = 30;
double  netdraw_start_angle = 90;

void ChangeNetdrawParams(NetdrawParams& params, int level)
{
  auto step = config::rotate_map_step;

  switch (level) {
    case 3 : case 4 : case 5 :
      helpers::ChangeTotalAngle(params, step);
      break;
    case 6 :
      helpers::ChangeTotalAngle(params, step);
      helpers::ChangeMiddleRadius(params, step, 20.0);
      break;
    case 7 :
      helpers::ChangeTotalAngle(params, step);
      helpers::ChangeMiddleAngle(params, step, 30.0);    
      break;
    case 8 : 
      helpers::ChangeTotalAngle(params, step);
      helpers::ChangeMiddleAngle(params, step);
      break;
    case 9 : 
      helpers::ChangeTotalAngle(params, step);
      helpers::ChangeMiddleAngle(params, -step*2);
      helpers::ChangeMiddleRadius(params, step, 20.0);
      break;
    case 10 :
      params.m_rad_offset_ = 0;
      helpers::ChangeTotalAngle(params, step);   
      helpers::ChangeMiddleAngle(params, -step*2); 
      break;
    case 11 :
      helpers::ChangeAllDoublesRandom(params);
      params.is_draw_digits_ = !params.is_draw_digits_;
      params.is_draw_poly_ = false;
      break;
    case 12 :
      helpers::ChangeAllDoublesRandom(params);
      params.is_draw_digits_ = !params.is_draw_digits_;
      params.is_draw_poly_ = false;
      break;
    case 13 :
      helpers::ChangeTotalAngle(params, step);   
      helpers::ChangeMiddleAngle(params, -step*2);
      helpers::ChangeMiddleRadius(params, step, 20.0);      
      params.is_draw_digits_ = true;
      params.is_draw_poly_ = true;
      break;
    case 14 :
      params = NetdrawParams();
      break;
  }
}

double  animation_speed = 0.03;
int     animation_step = 5;

double pi()
{
  return std::atan(1)*4;
}

int level_vertexes(int level)
{ 
  return (MapBase(level))*4;
}

double level_width(int)
{
  return level_vertexes(2) * edge_len * 2;
} 

double rotate_map_speed(int level)
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
    case 9 :
      return 0.04;
    case 10 : 
      return 0.02;
    case 11 : case 12 :
      return 1.0;
    case 13 :
      return 0.01;
    case 14 : default :
      return 0;
  }
}

double rotate_map_step = 0.3;

// LOGIC SETTINGS

int levels_max = 12;

int MapBase(int level)
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
      return level - 9;
  }
}

int RoomsCount(int level)
{
  return (MapBase(level) * 4);
}

int ArrowsCount(int level)
{ 
  if (level == 13)
    return RoomsCount(level) - 4;
  else
    return RoomsCount(level) / 4; 
}

int WumpsCount(int level)
{ 
  if (level == 13)
    return RoomsCount(level) - 4;
  else
    return RoomsCount(level) / 9; 
}

int BatsCount(int level)
{
  if (level == 13) 
    return 0;
  else
    return RoomsCount(level) / 9;
}

int PitsCount(int level)
{
  if (level == 13)
    return 0;
  else 
    return RoomsCount(level) / 9;    
}

}  // namespace conf

namespace helpers {

// Changes total angle of middle circle in NetdrawWidget

void ChangeTotalAngle(NetdrawParams& params, double step)
{
  params.start_angle_ += step;
}

// Changes angle offset of middle circle in NetdrawWidget

void ChangeMiddleAngle(NetdrawParams& params, double step)
{
  params.m_angle_offset_ += step;
}

// Changes angle offset of middle circle in Netdraw by range (+/-)

void ChangeMiddleAngle(NetdrawParams& params, double step, double range)
{
  if (params.m_angle_offset_ > (step * range))
    params.m_angle_offset_positive_ = false;
  else if (params.m_angle_offset_ < -(step * range * 2)) 
    params.m_angle_offset_positive_ = true;

  if (params.m_angle_offset_positive_)
    params.m_angle_offset_ += step;
  else
    params.m_angle_offset_ -= step * 2;
}

// Changes radius offset of middle circle in NetdrawWidget

void ChangeMiddleRadius(NetdrawParams& params, double step)
{
  params.m_rad_offset_ += step;
}

// Changes radius offset of middle circle in Netdraw by range (+/-)

void ChangeMiddleRadius(NetdrawParams& params, double step, double range)
{
  if (params.m_rad_offset_ > (step * range)) 
    params.m_rad_offset_positive_ = false;
  else if (params.m_rad_offset_ < -(step * range * 2))
    params.m_rad_offset_positive_ = true;

  if (params.m_rad_offset_positive_)
    params.m_rad_offset_ += step;
  else 
    params.m_rad_offset_ -= step * 2;
}

// Changes all parametrs contains doubles values in random order

void ChangeAllDoublesRandom(NetdrawParams& params)
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

}  // namespace helpers

}  // namespace wumpus_game