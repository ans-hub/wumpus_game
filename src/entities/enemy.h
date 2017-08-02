// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the abstract Enemy class

#ifndef ENEMY_H
#define ENEMY_H

#include "subject.h"

namespace wumpus_game {

class Enemy : public Subject
{
protected:
  explicit Enemy(Map* cave)
  : Subject(cave)
  { type_ = Subject::ENEMY; }
  virtual ~Enemy(){ }
};

}  // namespace wumpus_game

#endif  // ENEMY_H