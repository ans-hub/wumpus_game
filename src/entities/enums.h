// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: enumerations

#ifndef ENUMS_H
#define ENUMS_H

namespace wumpus_game {

enum class Person {
  UNKNOWN = 0,
  EMPTY,
  PLAYER,
  ENEMY,
  WUMP,
  PIT,
  BAT
};

}  // namespace wumpus_game

#endif  // ENUMS_H