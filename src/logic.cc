// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
  : level_(5,5,1,1,1) // make def ctor in level which is level 1
  , player_turn_{true}
  , game_over_cause_{Subject::EMPTY}
{

}

void Logic::NewLevel(unsigned int num)  // move level build logic in another class?? or file hel,pers?
{
  int base = static_cast<int>(num); // simulate assert
  int size = base + 3;
  int arrows = size;
  int wump = size*4/12;     // 
  int bat = size*4/12;      // increases to 1 unit when size increases to x/y
  int pit = size*4/6;       //
  level_ = Level(size, arrows, wump, bat, pit);
  game_over_cause_ = Subject::UNKNOWN;
  player_turn_ = true;
  NotifyObservers(Event::NEW_LEVEL);
  NotifyObservers(Event::READY_TO_INPUT);
}

void Logic::Turn(int action, int room)
{
  if (!game_over_cause_) {
    PlayerTurn(action, room);   // changes player_turn_;
  }
  if (!player_turn_ && !game_over_cause_) {
      PitsTurn();     //
      BatsTurn();     // changes game_over_ and player_turn_ 
      WumpsTurn();    //
    }
  if (!game_over_cause_) {
    NotifyObservers(Event::READY_TO_INPUT);
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
    default : NotifyObservers(Event::UNKNOWN_COMMAND); break;
  }
  player_turn_ = !does;
}

bool Logic::PlayerShot(int to_room)
{
  auto& player = level_.player_;
  auto& wumps  = level_.wumps_;
  auto cave   = level_.cave_.get();
  
  int from_room = player->GetCurrRoomNum();
  
  if (!helpers::is_neighboring_rooms(to_room, from_room, cave)) {
    NotifyObservers(Event::SHOT_NOT_NEIGHBOR);
    return false;
  }

  if (!player->Shot()) {
    game_over_cause_ = Subject::WUMP;
    NotifyObservers(Event::HAVE_NOT_ARROWS);
    NotifyObservers(Event::GAME_OVER);
    return false;
  }
  
  NotifyObservers(Event::PLAYER_DOES_SHOT);

  auto neighbors = helpers::get_neighboring_rooms(from_room, cave);
  helpers::worry_neighboring_wumps(wumps, neighbors);

  if (helpers::kill_one_wump_in_room(wumps, to_room)) {
    NotifyObservers(Event::ONE_WUMP_KILLED);
  }

  if (helpers::alive_subjects_count(wumps) == 0) {
    game_over_cause_ = Subject::PLAYER;
    NotifyObservers(Event::GAME_OVER);
  }
  return true;
}

bool Logic::PlayerMove(int room)
{
  auto& player = level_.player_;      
  
  std::string msg{""};
  if (!player->Move(room, msg)) {
    NotifyObservers(Event::MOVE_NOT_NEIGHBOR);
    return false; 
  }

  NotifyObservers(Event::PLAYER_DOES_MOVE);
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
      NotifyObservers(Event::GAME_OVER);      
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
      NotifyObservers(Event::MOVED_BATS);            
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
      NotifyObservers(Event::GAME_OVER);      
      break;
    }
  }
}

}  // namespace wumpus_game