// room.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: room of labyrinth interface
//
// Note #1 : contains subjects are currently placed in this room

#include <vector>

#ifndef ROOM_H
#define ROOM_H

namespace anshub {

class Subject;

struct Room
{
  typedef std::vector<Subject*> Vsubjects;

  Room() : Room(int()) { }
  explicit Room(int num)
  : num_{num}
  , left_{nullptr}
  , right_{nullptr}
  , back_{nullptr}
  , persons_{} { }
  Room(const Room&) =delete;

  bool IsEmpty() const;

  int       num_;
  Room*     left_;
  Room*     right_;
  Room*     back_;
  Vsubjects persons_;   // see note #1
};

}

#endif