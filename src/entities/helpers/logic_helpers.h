// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the logic helpers

#ifndef LOGIC_HELPERS_H
#define LOGIC_HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

#include "entities/subject.h"
#include "entities/room.h"
#include "entities/wump.h"
// #include "helpers/entities_helpers.h"

namespace wumpus_game {

namespace helpers {

  using VWumpsPtr = std::vector<std::unique_ptr<Wump>>;

  void worry_neighboring_wumps(VWumpsPtr&, std::vector<int>&);
  bool kill_one_wump_in_room(VWumpsPtr&, int);
  bool is_in_one_room(Subject*, Subject*);
  
  template<class T>
  int alive_subjects_count(std::vector<std::unique_ptr<T>>&);

  template<class T>
  int find_in_vector(std::vector<T>, T);


  // Template functions realisation

  template<class T>
  int alive_subjects_count(std::vector<std::unique_ptr<T>>& subj)
  {
    int result{0};
    for (const auto& s : subj) {
      if (s->IsLive()) ++result;
    }
    return result;
  }

  template<class T>
  int find_in_vector(std::vector<T> vec, T t)
  {
    int result{0};
    for (const auto& v : vec) {
      if (v == t) ++result;
    }
    return result;
  }

}  // namespace helpers

}  // namespace wumpus_game

#endif  // LOGIC_HELPERS_H