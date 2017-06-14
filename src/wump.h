// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Wumpus

#ifndef WUMP_H
#define WUMP_H

#include "enemy.h"

namespace anshub {

class Wump : public Enemy
{
public:
  explicit Wump(const Labyrinth& cave)
  : Enemy(cave)
  , worried_{false}
  { type_ = WUMP; }
  
  std::string FeelsRepresent() const override;
  bool Worried() const { return worried_; }
  void Worried(bool worried) { worried_ = worried; }
protected:
  bool worried_;
};

}  // namespace anshub

#endif  // WUMP_H