// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the map helpers

#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

// #include "entities/subject.h"
#include "entities/map.h"
#include "entities/room.h"

namespace wumpus_game {

namespace helpers {

  bool is_neighboring_rooms(int, int, Map*);
  std::vector<int> get_neighboring_rooms(int, Map*);
  std::string vint_to_string(const std::vector<int> &v, std::string delim = ",");
  // std::vector<Subject::ID> subjects_in_neighboring_rooms(int, Map*);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // MAP_HELPERS_H