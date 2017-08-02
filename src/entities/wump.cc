// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of the Wumpus

#include "wump.h"

namespace wumpus_game {
Wump::Wump(Map* cave) 
  : Enemy(cave)
  , worried_{false}
{
  type_ = Subject::WUMP;
}
}  // namespace wumpus_game