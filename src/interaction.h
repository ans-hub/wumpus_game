// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the class that represents interaction with user

#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <ios>
#include "3rdparty/cin_wrapper.h"    // used in InputActions()
// #include "gui.h"

namespace wumpus_game {

struct Interaction
{
  enum Actions
  {
    MOVE = 0,
    SHOT,
    HELP,
    QUIT
  };
  enum GameOverCause
  {
    NONE = 0,
    PLAYER,
    WUMP,
    PIT,
    USER
  };

  Interaction() : game_over_cause_{NONE} { }
  
  void    Say(const std::string& msg) const;
  void    SayIntro() const;
  void    SayRoomNeighbors(int, std::vector<int>) const;
  void    SayGameOver() const;
  
  void    OfferActions() const;
  Actions InputActions(int& room) const;
  
  void    GameOver(GameOverCause somewho) { game_over_cause_ = somewho; }
  bool    GameOver() const { return game_over_cause_; }
  
  GameOverCause game_over_cause_;
};

}  // namespace wumpus_game

#endif  // INTERACTION_H