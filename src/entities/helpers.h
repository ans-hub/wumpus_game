// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: general helpers

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
#include "entities/map.h"

namespace wumpus_game {

namespace helpers {

  using VWumpsPtr = std::vector<std::unique_ptr<Wump>>;

  void WorryNeighboringWumps(VWumpsPtr&, std::vector<int>&);
  bool KillOneWumpInRoom(VWumpsPtr&, int);
  bool IsInOneRoom(Subject*, Subject*);

  std::vector<Subject::ID> SubjectsInNeighboringRooms(int, Map*);
  std::string VintToString(const std::vector<int> &v, std::string delim = ",");

  template<class T>
  int AliveSubjectsCount(const std::vector<std::unique_ptr<T>>&);
  
  template<class T>
  int FindInVector(std::vector<T>, T);

  // Template functions implementation
  
  template<class T>
  int AliveSubjectsCount(const std::vector<std::unique_ptr<T>>& subj)
  {
    int result{0};
    for (const auto& s : subj) {
      if (s->IsLive()) ++result;
    }
    return result;
  }

  template<class T>
  int FindInVector(std::vector<T> vec, T t)
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