// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the test helpers

#include "test_helpers.h"

namespace wumpus_game {

namespace test_helpers {

// Returns roomses numbers where person is

std::vector<int> rooms_with_persons(const Map& cave, Subject::Person subj)
{
  std::vector<int> result{};
  for (int i = 0; i < cave.GetSize(); ++i) {
    auto curr_persons = cave.GetRoom(i)->persons_;
    for (const auto& p : curr_persons) {
      if (p->GetType() == subj) result.push_back(p->GetCurrRoomNum());
    }
  }
  return result;
}

// Counts concrete person instances in cave

int persons_in_cave(const Map& cave, Subject::Person subj)
{
  return static_cast<int>(rooms_with_persons(cave, subj).size());
}

// Returns room number of concrete person (minus if not find)

int find_person_in_cave(const Map& cave, Subject* subj)
{
  int result{-1};
  for (int i = 0; i < cave.GetSize(); ++i) {
    auto curr_persons = cave.GetRoom(i)->persons_;
    for (const auto& p : curr_persons) {
      if (p == subj) result = p->GetCurrRoomNum();
      break;
    }
  }
  return result;
}


}  // namespace helpers

}  // namespace wumpus_game