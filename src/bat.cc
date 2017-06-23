// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Bat class

#include "bat.h"

namespace wumpus_game {

std::string Bat::FeelsRepresent() const
{
  return "FEELS: You feel the wind (possible the bats is near)";
}

}  // namespace wumpus_game