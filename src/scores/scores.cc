// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents player scores in game

#include "scores.h"

namespace wumpus_game {

Scores::Scores(const Config& conf, const Logic& logic)
  : conf_{conf}
  , logic_{logic}
{

}

bool Scores::IncomingNotify(Event msg)
{
  return true;
}

}  // namespace wumpus_game