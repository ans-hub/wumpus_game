// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Room class

#ifndef ROOM_H
#define ROOM_H

#include <vector>

namespace wumpus_game {

class Subject;

struct Room
{
  typedef std::vector<const Subject*> Vsubjects;  // see note #1 after code

  Room() : Room(int()) { }
  explicit Room(int num)
  : num_{num}
  , left_{nullptr}
  , right_{nullptr}
  , back_{nullptr}
  , persons_{} { }
  Room(const Room&) =delete;
  Room& operator=(Room&) =delete;
  Room(Room&&) =delete;
  Room& operator=(Room&&) =delete;

  bool IsEmpty() const;

  int       num_;
  Room*     left_;
  Room*     right_;
  Room*     back_;
  Vsubjects persons_;   // see note #2 after code
};

}  // namespace wumpus_game

#endif  // ROOM_H

// Implementation notes:
//
// #1: slicing. More right way to do this data member private, and
// implement interface to push and pop elements
//
// #2: contains subjects are currently placed in this room