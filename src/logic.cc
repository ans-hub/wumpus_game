// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
  : level_(5,5,1,1,1) // make def ctor in level which is level 1
  , player_turn_{true}
  , game_over_cause_{Subject::UNKNOWN}
{
  NewLevel(1);
}

void Logic::NewLevel(unsigned int num)
{
  int base = static_cast<int>(num); // simulate assert
  int size = base + 3;
  int arrows = 5;
  int wump = size*4/12;   // 
  int bat = size*4/6;     // increases to 1 unit when size increases to x/y
  int pit = size*4/12;    //
  level_ = Level(size, arrows, wump, bat, pit);
  game_over_cause_ = Subject::UNKNOWN;
}

void Logic::Turn(int action, int room)
{
  if (!game_over_cause_) {
    PlayerTurn(action, room);   // changes player_turn_;
    if (!player_turn_) {
      PitsTurn();     //
      BatsTurn();     // changes game_over_ and player_turn_ 
      WumpsTurn();    //
    }
  }
}

void Logic::PlayerTurn(int action, int room)
{
  player_turn_ = true;
  bool does = false;
  switch (action) 
  {
    case 0 : does = PlayerMove(room); break;
    case 1 : does = PlayerShot(room); break;
  }
  player_turn_ = !does;
}

bool Logic::PlayerShot(int to_room)
{
  auto& player = level_.player_;
  auto& wumps  = level_.wumps_;
  auto& cave  = level_.cave_;
  
  int from_room = player->GetCurrRoomNum();
  
  if (!helpers::is_neighboring_rooms(to_room, from_room, cave)) {
    // NotifyObservers(Event::DOES_NOT_SHOT_A);
    return false;
  }

  if (!player->Shot()) {
    // NotifyObservers(Event::DOES_NOT_SHOT_B);
    return false;
  }

  auto neighbors = helpers::get_neighboring_rooms(from_room, cave);
  helpers::worry_neighboring_wumps(wumps, neighbors);
  if (helpers::kill_one_wump_in_room(wumps, to_room)) {
    // Notidy
  }

  if (helpers::alive_subjects_count(level_.wumps_) == 0) {
    game_over_cause_ = Subject::PLAYER;
    // NotifyObservers(Event::PLAYER_WIN);
  }
  // NotifyObservers(Event::PLAYER_END_SHOT);
  return true;
}

bool Logic::PlayerMove(int room)
{
  auto& player = level_.player_;      
  
  std::string msg{""};
  if (!player->Move(room, msg)) {
    // NotifyObservers(Event::DOES_NOT_MOVE);
    return false; 
  }
  
  // NotifyObservers(Event::PLAYER_MOVED);
  return true;
}

void Logic::WumpsTurn()
{
  auto& player = level_.player_;      
  auto& wumps = level_.wumps_;
  
  for (auto& wump : wumps) {
    if (wump->Worried()) {
      wump->MoveRandom();
      wump->Worried(false);
    }
    if (helpers::is_in_one_room(wump.get(), player.get())) {
      player->Kill();
      game_over_cause_ = Subject::WUMP;
      break;
    }
  }
}

void Logic::BatsTurn()
{
  auto& player = level_.player_;    
  auto& bats = level_.bats_;

  for (auto& bat : bats) {
    if (helpers::is_in_one_room(bat.get(), player.get())) {
      player->TeleportRandom();
      bat->TeleportRandom();
      break;
    }
  }  
}

void Logic::PitsTurn()
{
  auto& player = level_.player_;  
  auto& pits = level_.pits_;

  for (auto& pit : pits) {
    if (helpers::is_in_one_room(pit.get(), player.get())) {
      player->Kill();
      game_over_cause_ = Subject::PIT;
      break;
    }
  }
}

}  // namespace wumpus_game