// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the abstract Enemy class

#ifndef ENEMY_H
#define ENEMY_H

#include "subject.h"

namespace anshub {

class Enemy : public Subject
{
public:
  explicit Enemy(const Labyrinth& cave)
  : Subject(cave)
  { type_ = ENEMY; }
  ~Enemy(){ }
  
  // Represents what feels others if near placed the Enemy

  virtual std::string FeelsRepresent() const =0;
};

}  // namespace anshub

#endif  // ENEMY_H