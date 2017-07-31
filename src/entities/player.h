// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "entities/subject.h"

namespace wumpus_game {

class Player : public Subject
{
public:
  explicit Player(Map*, int);
  ~Player() { }
  Player(Player&& old);
  Player& operator=(Player&&);
  
  bool        Shot();
  VSubjectsId Feels() const;
  int GetArrows() const { return arrows_; }
private:
  int arrows_;
};

}  // namespace wumpus_game

#endif  // PLAYER_H