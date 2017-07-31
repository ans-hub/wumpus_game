// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the bottomless Pit class

#ifndef PIT_H
#define PIT_H

#include "entities/enemy.h"

namespace wumpus_game {

class Pit : public Enemy
{
public:
  explicit Pit(Map* cave)
  : Enemy(cave)
  { type_ = Subject::PIT; }
  
  std::string FeelsRepresent() const override;
};

}  // namespace wumpus_game

#endif  // PIT_H