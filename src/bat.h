// bat.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: bat class

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

}

#endif