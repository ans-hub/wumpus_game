// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Map class

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "room.h"

namespace wumpus_game {

class Map
{
public:
  typedef std::vector<Room*> Vrooms;
  
  explicit Map(int);
  ~Map();
  Map(const Map&) =delete;

  Room*   GetRoom(int num) const;
  int     GetSize() const { return size_; }

protected:
  void    CreateRooms();
  void    ConnectRooms();

  int     size_;
  Vrooms  rooms_;
};

std::ostream& operator<<(std::ostream&, const Map&);

}  // namespace wumpus_game

#endif  // LABYRINTH_H