// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between model and view 

#ifndef EVENTS_H
#define EVENTS_H

namespace wumpus_game {

  enum class Events
  {
    WINDOW = 0,
    INTRO,
    GAME_OVER,
    PROMPT,
    ERROR_ROOM,
    ERROR_ACTION,
    NEIGH_ROOMS,
    PLAYER_FEELS,
    MOVED_BATS,
    PLAYER_MOVED
  };

}  // namespace mvc_set

#endif  // MVC_SET_MESSAGE