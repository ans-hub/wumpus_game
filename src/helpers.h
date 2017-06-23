// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the helpers

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "labyrinth.h"
#include "room.h"

namespace wumpus_game {

namespace helpers {

  bool is_neighboring_rooms(int, int, const Labyrinth&);
  std::vector<int> get_neighboring_rooms(int, const Labyrinth&);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // HELPERS_H