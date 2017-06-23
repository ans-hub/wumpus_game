// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of the Wumpus

#include "wump.h"

namespace wumpus_game {

std::string Wump::FeelsRepresent() const
{
  return "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)";
}

}  // namespace wumpus_game