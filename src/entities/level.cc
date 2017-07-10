// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: game level

#include "level.h"

namespace wumpus_game {

Level::Level(int size, int wumps, int pits, int bats)
  : cave_{size}
  , player_{cave_}
  , wumps_{ } 
  , bats_ { }
  , pits_ { }
{
  for (int i = 0; i < wumps; ++i)
    wumps_.push_back(WumpPtr {new Wump(cave_)});
  for (int i = 0; i < bats; ++i)
    bats_.push_back(BatPtr {new Bat(cave_)});
  for (int i = 0; i < pits; ++i)
    pits_.push_back(PitPtr {new Pit(cave_)});
}

Level::Level(Level&& old)
  : cave_{std::move(old.cave_)}
  , player_{std::move(old.player_)}
  , wumps_{std::move(old.wumps_)}
  , bats_{std::move(old.bats_)}
  , pits_{std::move(old.pits_)}
{

}

}  // namespace wumpus_game