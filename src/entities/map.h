// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Map

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "entities/room.h"

namespace wumpus_game {

class Map
{
public:
  typedef std::vector<Room*> Vrooms;
  
  explicit Map(int);
  ~Map();
  Map(const Map&) =delete;
  Map& operator=(const Map&) =delete;
  Map(Map&&);
  Map& operator=(Map&&);

  Room*   GetRoom(int num) const;
  int     GetSize() const { return size_; }

protected:
  void    CreateRooms();
  void    ConnectRooms();

  int     base_;
  int     size_;
  Vrooms  rooms_;
};

std::ostream& operator<<(std::ostream&, const Map&);

namespace map_helpers {

  bool IsNeighboringRooms(int, int, Map*);
  std::vector<int> GetNeighboringRooms(int, Map*);

}  // namespace map_helpers

}  // namespace wumpus_game

#endif  // MAP_H