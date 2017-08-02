// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between model and view

#ifndef EVENTS_H
#define EVENTS_H

namespace wumpus_game {

  enum class Event
  {
    MODEL_READY = 0,
    UNKNOWN_COMMAND,
    READY_TO_INPUT,
    NEW_LEVEL,
    GAME_OVER,
    MOVED_BATS,
    HAVE_NOT_ARROWS,
    SHOT_NOT_NEIGHBOR,
    MOVE_NOT_NEIGHBOR,
    PLAYER_DOES_SHOT,
    PLAYER_DOES_MOVE,
    ONE_WUMP_KILLED
  };

}  // namespace wumpus_game

#endif  // EVENTS_H