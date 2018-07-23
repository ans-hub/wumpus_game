// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: represents scores in game

#ifndef SCORES_H
#define SCORES_H

#include "3rdparty/observer.h"
#include "entities/logic.h"
#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

struct Scores : public mvc_set::Observer<Event>
{
  explicit Scores(const Logic&);
  ~Scores() { }
private:
  bool IncomingNotify(Event) override;
  const Logic&  logic_;
};

}  // namespace wumpus_game

#endif  // SCORES_H