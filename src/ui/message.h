// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between controllor, view and model 

#ifndef MVC_SET_MESSAGE
#define MVC_SET_MESSAGE

namespace mvc_set {

// struct Message
// {
  enum class Message
  {
    SHOW_VIEW = 0,
    SHOW_INTRO,
    SHOW_GAME_OVER,
    SHOW_REQ_INPUT,
    SHOW_NEIGH_ROOMS,
    FEEL_WUMP,
    FEEL_PIT,
    FEEL_BAT,
    GAME_START,
    PLAYER_MOVE,
    PLAYER_SHOT
  };
// };

}  // namespace mvc_set

#endif  // MVC_SET_MESSAGE