// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents current configuration in game

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>

namespace wumpus_game {

struct Config
{
  Config()
    : snd_click_{"audio/wav/click.wav"}
    , snd_background_{"audio/wav/cave_theme_2.mp3"}
    , snd_steps_{"audio/wav/player_walk.wav"}
    , snd_bats_{"audio/wav/bats_movement.wav"}
    , snd_wump_attack_{"audio/wav/wump_attack.wav"}
    , snd_wump_killed_{"audio/wav/wump_killed.wav"}
    , snd_wump_feels_{"audio/wav/wump_feels.wav"}
    , snd_unknown_act_{"audio/wav/unknown_action.wav"}
    , snd_pits_{"audio/wav/player_pits.wav"}
    , snd_shot_{"audio/wav/player_shot.wav"}
    { }
  std::string snd_click_;
  std::string snd_background_;
  std::string snd_steps_;
  std::string snd_bats_;
  std::string snd_wump_attack_;
  std::string snd_wump_killed_;
  std::string snd_wump_feels_;
  std::string snd_unknown_act_;
  std::string snd_pits_;
  std::string snd_shot_; 
};

}  // namespace wumpus_game

#endif  // GAME_CONFIG_H