// wump.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: wump class

#ifndef WUMP_H
#define WUMP_H

#include "enemy.h"

namespace anshub {

class Wump : public Enemy
{
public:
  explicit Wump(Labyrinth* cave) : Enemy(cave) , worried_{false} { type_ = WUMP; }
  
  std::string FeelsRepresent() const override;
  bool Worried() const { return worried_; }
  void Worried(bool worried) { worried_ = worried; }
protected:
  bool worried_;
};

}

#endif