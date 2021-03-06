// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Wumpus

#ifndef WUMP_H
#define WUMP_H

#include "entities/enemy.h"

namespace wumpus_game {

class Wump : public Enemy
{
public:
  explicit Wump(Map*);
  ~Wump(){ }
  bool Worried() const { return worried_; }
  void Worried(bool worried) { worried_ = worried; }
protected:
  bool worried_;
};

}  // namespace wumpus_game

#endif  // WUMP_H