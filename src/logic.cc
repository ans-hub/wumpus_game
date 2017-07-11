// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
  : level_(5,1,1,1)
  , game_over_cause_{Person::UNKNOWN}
{
  NewLevel(1);
}

void Logic::NewLevel(unsigned int num)
{
  int base = static_cast<int>(num); // simulate assert
  int size = base + 3;
  int wump = size*4/12;   // 
  int bat = size*4/6;     // increases to 1 unit when size increases to x/y
  int pit = size*4/12;    //
  level_ = Level(size ,wump, bat, pit);
  game_over_cause_ = Person::UNKNOWN;
}

void Logic::Move(int room)
{
  // auto& player = level_.player_;

  // bool is_moved = helpers::move_subject(level_->player_, room);
  // if (!is_moved) {
    // NotifyObservers();
    // return;
  // }

  // auto player_sees = helpers::dpersons_in_room(room);
  // for(auto const person : player_sees) {
    // switch(person->GetType())
    // {
    //   case Person::WUMP :
    //     player->Kill();
    //     game_over_cause_ = Person::WUMP;
    //     return;
    //   case Person::PIT  :
    //     player->Kill();
    //     game_over_cause_ = Person::PIT;
    //     return;
    //   case Person::BAT  :
    //     player->TeleportRandom();
    //     person->TeleportRandom();
    //     // NotifyViews(Show::MOVED_BATS);
    //     break;
    //   default : break;
    // }
  // }
}

void Logic::Shot(int room)
{
  auto& player = level_.player_;

  auto killed = player->Shot(room);
}


}  // namespace wumpus_game