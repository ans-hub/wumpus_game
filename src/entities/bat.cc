// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Bat class

#include "bat.h"

namespace wumpus_game {

Bat::Bat(Map* cave) : Enemy(cave)
{
  type_ = Subject::BAT;
}

}  // namespace wumpus_game