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
public:
  explicit Enemy(Map& cave)
  : Subject(cave)
  { type_ = Person::ENEMY; }
  ~Enemy(){ }
  
  // Represents what feels others if near placed the Enemy

  virtual std::string FeelsRepresent() const =0;
};

}  // namespace wumpus_game

#endif  // ENEMY_H