// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enumerations

#ifndef ENUMS_H
#define ENUMS_H

namespace wumpus_game {

  // Used by observers and observable
  
  enum class Event
  {
    MODEL_READY = 0,
    UNKNOWN_COMMAND,
    READY_TO_INPUT,
    NEW_LEVEL,
    GAME_OVER,
    MOVED_BY_BATS,
    HAVE_NOT_ARROWS,
    SHOT_NOT_NEIGHBOR,
    MOVE_NOT_NEIGHBOR,
    PLAYER_DOES_SHOT,
    PLAYER_DOES_MOVE,
    ONE_WUMP_KILLED,
    MEETS_GUIDE
  };

  // Used by WidgetPlayer

  enum class PlayerState
  {
    STAY = 0,
    WALK,
    SHOT,
    MOVED_BY_BATS,
    KILLED_BY_WUMP,
    KILLED_BY_PITS,
    MEETS_CLOSED_GUIDE,
    KILL_WUMP,
    LEVEL_WIN,
    HAVENT_ARROWS,
    FEELS_WUMP,
    FEELS_BATS,
    FEELS_PITS,
    UNKNOWN_STATE
  };

  // Used by WidgetRoom

  enum class RoomState
  {
    DARK,
    LIGHT,
    GATE,
    GUIDE_OPENED,
    GUIDE_CLOSED
  };

  // Used by WidgetInfo

  enum class InfoStuff
  {
    COVER,
    ARROWS,
    PITS,
    BATS,
    WUMPS,
    LEVEL,
    CONTINUE_IMAGE,
    CONTINUE_DEIMAGE
  };
   
}  // namespace wumpus_game

#endif  // EVENTS_H