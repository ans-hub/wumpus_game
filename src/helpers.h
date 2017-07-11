// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the helpers

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "entities/subject.h"
#include "entities/map.h"
#include "entities/room.h"

namespace wumpus_game {

namespace helpers {

  bool is_neighboring_rooms(int, int, const Map&);
  std::vector<int> get_neighboring_rooms(int, const Map&);
  std::string vint_to_string(const std::vector<int> &v, std::string delim = ",");

  template<class T> int find_in_vector(std::vector<T>, T);

  // Template functions realisation

  template<class T> int find_in_vector(std::vector<T>, T)
  {
    int result{0};
    return result;
  }

}  // namespace helpers

}  // namespace wumpus_game

#endif  // HELPERS_H