// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between controllor, view and model 

#ifndef MVC_SET_EVENTS
#define MVC_SET_EVENTS

namespace mvc_set {

  enum class Show   // Event
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

  enum class Input  // Action
  { 
    UNKNOWN,
    HELP,
    QUIT,
    MOVE,
    SHOT
  };

}  // namespace mvc_set

#endif  // MVC_SET_MESSAGE