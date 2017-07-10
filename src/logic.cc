// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
  : level_{20,1,1,1}
  , game_over_cause_{Person::UNKNOWN}
{ 
  Init();
}

void Logic::Init()
{
  // level_ = Level(1,1,1,1);
  game_over_cause_ = Person::UNKNOWN;
}


}  // namespace mvc_set