// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: game level

#include "level.h"

namespace wumpus_game {

Level::Level()
  : cave_{}
  , player_{}
  , wumps_{} 
  , bats_{}
  , pits_{} { }

Level::Level(int size, int arrows, int wumps, int bats, int pits)
  : cave_{}
  , player_{}
  , wumps_{} 
  , bats_{}
  , pits_{}
{
  cave_ = MapPtr {new Map{size}};
  player_ = PlayerPtr {new Player(cave_.get(), arrows)};
  for (int i = 0; i < wumps; ++i)
    wumps_.push_back(WumpPtr {new Wump(cave_.get())});
  for (int i = 0; i < bats; ++i)
    bats_.push_back(BatPtr {new Bat(cave_.get())});
  for (int i = 0; i < pits; ++i)
    pits_.push_back(PitPtr {new Pit(cave_.get())});
}

Level::Level(Level&& old)
  : cave_{std::move(old.cave_)}
  , player_{std::move(old.player_)}
  , wumps_{std::move(old.wumps_)}
  , bats_{std::move(old.bats_)}
  , pits_{std::move(old.pits_)} { }

Level& Level::operator=(Level&& old)
{
  cave_.swap(old.cave_);
  player_ = std::move(old.player_);
  wumps_.swap(old.wumps_);
  bats_ = std::move(old.bats_);
  pits_ = std::move(old.pits_);
  return *this;
}

int Level::WumpsCountLive() const
{
  int lives{0};
  for (const auto& v : wumps_)
    if (v->IsLive()) ++lives;
  return lives;
}


}  // namespace wumpus_game