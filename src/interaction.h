// interaction.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: user interaction class
//
// Note #1 : used in InputActions() to simplify coding of user input

#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <ios>
#include "3rdparty/cin_wrapper.h"    // see note #1

namespace anshub {

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
  void    GameOver(GameOverCause somewho) { game_over_cause_ = somewho; }
  bool    GameOver() const { return game_over_cause_; }
  void    Say(const std::string& msg) const;
  void    SayIntro() const;
  void    SayRoomNeighbors(int, std::vector<int>) const;
  void    SayGameOver() const;
  void    OfferActions() const;
  Actions InputActions(int& room) const;

  GameOverCause game_over_cause_;
};

}

#endif