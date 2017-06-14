// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Bat class

#ifndef BAT_H
#define BAT_H

#include "enemy.h"

namespace anshub {

class Bat : public Enemy
{
public:
  explicit Bat(const Labyrinth& cave)
  : Enemy(cave)
  { type_ = BAT; }
  
  std::string FeelsRepresent() const override;
};

}  // namespace anshub

#endif  // BAT_H