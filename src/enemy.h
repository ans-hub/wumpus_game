// enemy.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: enemy abstract class

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
  virtual std::string FeelsRepresent() const =0;
};

}

#endif