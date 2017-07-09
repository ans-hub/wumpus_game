// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the test helpers

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "entities/map.h"
#include "entities/subject.h"

namespace wumpus_game {

namespace test_helpers {

  int persons_in_cave(const Map&, Subject::Person);

}  // namespace test_helpers

}  // namespace wumpus_game

#endif  // TEST_HELPERS_H