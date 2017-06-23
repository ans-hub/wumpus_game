// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of the bottomless Pit class

#include "pit.h"

namespace wumpus_game {

std::string Pit::FeelsRepresent() const
{
  return "FEELS: You feel the cold (possible the bottomless pit is near)";
}

}  // namespace wumpus_game