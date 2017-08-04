// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents sounds in game

#ifndef SCORES_H
#define SCORES_H

#include "3rdparty/observer.h"
#include "entities/events.h"
#include "entities/logic.h"
#include "settings/config.h"

namespace wumpus_game {

struct Scores : public mvc_set::Observer<Event>
{
  Scores(const Logic&, const Config&);
  ~Scores();
private:
  bool IncomingNotify(Event) override;
  const Logic&  logic_;
  const Config& config_;
};

}  // namespace wumpus_game

#endif  // SCORES_H