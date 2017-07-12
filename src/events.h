// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between model and view 

#ifndef EVENTS_H
#define EVENTS_H

namespace wumpus_game {

  enum class Event
  {
    WINDOW = 0,
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
    ONE_WUMP_KILLED,
    // INTRO,
    // GAME_OVER,
    // PROMPT,
    // ERROR_ROOM,
    // ERROR_ACTION,
    // NEIGH_ROOMS,
    // PLAYER_FEELS,
    // MOVED_BATS,
    // PLAYER_MOVED
  };

}  // namespace mvc_set

#endif  // MVC_SET_MESSAGE