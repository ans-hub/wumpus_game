// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents current configuration in game

#include "config.h"

namespace wumpus_game {

namespace config {

std::string GetBgMusic(int level)
{
  if (level < 4) return "audio/wav/theme_cave.wav";
  if (level < 7) return "audio/wav/theme_underwater.mp3";
  if (level < 11) return "audio/wav/theme_dead_town.ogg";
  return "";
}

std::string GetSound(PlayerState type)
{
  switch(type) {
    case PlayerState::MOVED_BY_BATS : return "audio/wav/bats_movement.wav"; break;
    case PlayerState::WALK : return "audio/wav/player_walk.wav"; break;
    case PlayerState::SHOT : return "audio/wav/player_shot.wav"; break;
    case PlayerState::KILLED_BY_PITS : return "audio/wav/player_pits.wav"; break;
    case PlayerState::KILLED_BY_WUMP : return "audio/wav/wump_attack.wav"; break;
    case PlayerState::KILL_WUMP : return "audio/wav/wump_killed.wav"; break;
    case PlayerState::HAVENT_ARROWS : return "audio/wav/click.wav"; break;
    case PlayerState::FEELS_WUMP : return "audio/wav/wump_feels.wav"; break;
    case PlayerState::UNKNOWN_ACTION : return "audio/wav/click.wav"; break;
    default : break;
  }
  return "";
}

std::string GetBgImage(int level)
{
  if (level < 4) return "gui/forms/img/cv_main.png";
  if (level < 7) return "gui/forms/img/uw_main.png";
  if (level < 11) return "gui/forms/img/dt_main.png";
  return "";
}

// GUI SETTINGS

double  edge_len = 12;
int     room_btn_size = 30;
int     main_wnd_offset = 30;
double  animation_speed = 0.03;
int     animation_step = 5;

double pi()
{
  return std::atan(1)*4;
}

int level_vertexes(int level)
{ 
  return (map_base(level))*4;
}

double level_width(int)
{
  return level_vertexes(2) * edge_len * 2;
} 

double rotate_map_speed(int level)
{
  if (level < 4) return 0;
  if (level < 5) return 0.05;
  if (level < 6) return 0.04;
  if (level < 7) return 0.03;
  if (level < 8) return 0.06;
  if (level < 9) return 0.05;
  if (level < 10) return 0.04;
  if (level < 11) return 0.02;
  return 0;
}

double rotate_map_step = 0.3;

// LOGIC SETTINGS

int levels_max = 12;

int map_base(int level)
{
  if (level < 4) return level + 4;
  if (level < 7) return level + 1;
  if (level < 11) return level - 2;
  // return level + 4;
  return 1; 
}

int rooms_cnt(int level) { return (map_base(level) * 4); }

int arrows_cnt(int level) { return rooms_cnt(level) / 4; }

int wumps_cnt(int level) { return rooms_cnt(level) / 9; }

int bats_cnt(int level) { return rooms_cnt(level) / 9; }

int pits_cnt(int level) { return rooms_cnt(level) / 9; }

}  // namespace conf

}  // namespace wumpus_game