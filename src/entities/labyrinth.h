// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Labyrinth class

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "room.h"

namespace wumpus_game {

class Labyrinth
{
public:
  typedef std::vector<Room*> Vrooms;
  
  explicit Labyrinth(int);
  ~Labyrinth();
  Labyrinth(const Labyrinth&) =delete;

  Room*   GetRoom(int num) const;
  int     GetSize() const { return size_; }

protected:
  void    CreateRooms();
  void    ConnectRooms();

  int     size_;
  Vrooms  rooms_;
};

std::ostream& operator<<(std::ostream&, const Labyrinth&);

}  // namespace wumpus_game

#endif  // LABYRINTH_H