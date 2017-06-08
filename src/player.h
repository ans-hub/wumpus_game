// player.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: player class

#ifndef PLAYER_H
#define PLAYER_H

#include "subject.h"

namespace anshub {

class Player : public Subject
{
public:
  explicit Player(Labyrinth* cave) : Subject(cave) { type_ = PLAYER; }
  ~Player() { }
  Persons Feels() const;
  Person  Shot(int) const;
};

}

#endif