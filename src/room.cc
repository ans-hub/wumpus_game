// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Room class

#include "room.h"

namespace anshub {

bool Room::IsEmpty() const
{
  return (persons_.empty()) ? true : false;
}

}  // namespace anshub