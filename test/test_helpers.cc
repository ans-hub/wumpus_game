// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the test helpers

#include "test_helpers.h"

namespace wumpus_game {

namespace test_helpers {

// Counts concrete person instances in cave

int persons_in_cave(const Map& cave, Subject::Person subj)
{
  int result{0};
  for (int i = 0; i < cave.GetSize(); ++i) {
    auto curr_persons = cave.GetRoom(i)->persons_;
    for (const auto& p : curr_persons) {
      if (p->GetType() == subj) ++result;
    }
  }
  return result;
}

}  // namespace helpers

}  // namespace wumpus_game