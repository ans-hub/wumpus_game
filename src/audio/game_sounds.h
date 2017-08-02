// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents sounds in game

#ifndef GAME_SOUNDS_H
#define GAME_SOUNDS_H

#include <vector>

#include "3rdparty/bass.h"
#include "3rdparty/observer.h"
#include "entities/events.h"

namespace wumpus_game {

struct GameSounds : public mvc_set::Observer<Event>
{
  using Handles = std::vector<HSAMPLE>;

  enum Type {
    BACKGROUND,
    WALK,
    SHOT
  };

  GameSounds();
  ~GameSounds();
  bool Inited() const { return inited_; }
  void Play(const char*, bool);
private:
  bool IncomingNotify(Event) override;
  bool inited_;
  Handles handles_;
};

}  // namespace wumpus_game

#endif  // GAME_SOUNDS_H