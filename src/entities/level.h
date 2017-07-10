// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: game level

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>

#include "entities/map.h"
#include "entities/player.h"
#include "entities/wump.h"
#include "entities/bat.h"
#include "entities/pit.h"

namespace wumpus_game {

struct Level
{
  using PlayerPtr = std::unique_ptr<Player>;
  using WumpPtr   = std::unique_ptr<Wump>;
  using BatPtr    = std::unique_ptr<Bat>;
  using PitPtr    = std::unique_ptr<Pit>;

  using WumpsVec  = std::vector<WumpPtr>;
  using BatsVec   = std::vector<BatPtr>;
  using PitsVec   = std::vector<PitPtr>;

  Map       cave_;
  PlayerPtr player_;
  WumpsVec  wumps_;
  BatsVec   bats_;
  PitsVec   pits_;

  Level(int, int, int, int);
  Level(const Level&) =delete;
  Level& operator=(const Level&) = delete;
  Level(Level&&);
  Level& operator=(Level&&);
};

}  // namespace wumpus_game

#endif  // LEVEL_H