// pit.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: the bottomless pit class

#ifndef PIT_H
#define PIT_H

#include "enemy.h"

namespace anshub {

class Pit : public Enemy
{
public:
  explicit Pit(Labyrinth* cave) : Enemy(cave) { type_ = PIT; }
  std::string FeelsRepresent() const override;
};

}

#endif