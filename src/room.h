// room.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: room of labyrinth interface
// 
// Note #1 : slicing. More right way to do this data member private, and
// implement interface to push and pop elements
// Note #2 : contains subjects are currently placed in this room

#include <vector>

#ifndef ROOM_H
#define ROOM_H

namespace anshub {

class Subject;

struct Room
{
  typedef std::vector<const Subject*> Vsubjects;  // see note #1

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
  Vsubjects persons_;   // see note #2
};

}

#endif