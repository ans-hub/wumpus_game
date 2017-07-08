// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Bat class

#ifndef BAT_H
#define BAT_H

#include "enemy.h"

namespace wumpus_game {

class Bat : public Enemy
{
public:
  explicit Bat(const Map& cave)
  : Enemy(cave)
  { type_ = BAT; }
  
  std::string FeelsRepresent() const override;
};

}  // namespace wumpus_game

#endif  // BAT_H