// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: game level

#include "level.h"

namespace wumpus_game {

Level::Level(int size, std::size_t wumps, std::size_t pits, std::size_t bats)
  : cave_{size}
  , player_{cave_}
  , wumps_{ } 
  , bats_ { }
  , pits_ { }
{
  for (std::size_t i = 0; i < wumps; ++i)
    wumps_.push_back(WumpPtr {new Wump(cave_)});
  for (std::size_t i = 0; i < bats; ++i)
    bats_.push_back(BatPtr {new Bat(cave_)});
  for (std::size_t i = 0; i < pits; ++i)
    pits_.push_back(PitPtr {new Pit(cave_)});
}

}  // namespace wumpus_game