// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the test helpers

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <vector>

#include "entities/map.h"
#include "entities/subject.h"

namespace wumpus_game {

namespace test_helpers {

  std::vector<int> rooms_with_persons(const Map&, Subject::ID);
  int persons_in_cave(const Map&, Subject::ID);
  int find_person_in_cave(const Map&, Subject*);
  std::vector<Subject*> neighboring_subjects(Subject&, const Map&);


}  // namespace test_helpers

}  // namespace wumpus_game

#endif  // TEST_HELPERS_H