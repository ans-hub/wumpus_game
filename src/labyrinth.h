// labyrinth.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: labyrinth interface

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "room.h"

namespace anshub {

class Labyrinth
{
public:
  typedef std::vector<int>   Vint;
  typedef std::vector<Room*> Vrooms;
  
  explicit Labyrinth(int);
  ~Labyrinth();
  Labyrinth(const Labyrinth&) =delete;

  Room*   GetRoom(int num) const;
  int     GetSize() const { return size_; };
  bool    IsNeighbors(int, int) const;
  Vint    GetNeighbors(int) const;
  void    DebugOutput(std::ostream& oss);

protected:
  void    CreateRooms();
  void    ConnectRooms();

  int     size_;
  Vrooms  rooms_;
};

}

#endif