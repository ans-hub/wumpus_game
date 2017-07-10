// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Map class
//
// Note #1 : Implementation of map based on directed graph with the
// degree of valency of all vertexes equal 3 (every vertex is connected by
// edges with 3 other vertex. In meaning of this app the Map is the
// Graph, the Rooms are vertexes and the tunnels are edges, the size is the
// Rooms count in the Map.
//
// Note #2 : Connecting of the Rooms is auto-processed and based on plane
// projection of regular dodecahedron using Schlegel diagram. Neighbors
// Rooms are called as "left", "right" and "back". As you can see at the
// plane projection, here are presence three main pathes, called "center",
// "outer" and "inner". Center path consists of size/2 rooms, outer and inner
// pathes consists of size/4 rooms. Manually creating was avoided by me as
// not extentable. Scheme of connecting see in the /src/graph.jpg

#include "map.h"

namespace wumpus_game {

Map::Map(int size) : size_{size}, rooms_{}
{
  CreateRooms();    // create graph (see note #1)
  ConnectRooms();   // connect vertexes of graph (see note #2)
}

Map::~Map()
{
  for (auto r : rooms_) {
    if (r) delete r;
  }
}

Map::Map(Map&& old) : size_{old.size_}, rooms_{old.rooms_}
{
  old.size_ = 0;
  for (auto& r : old.rooms_)  r = nullptr;
}

Map& Map::operator=(Map&& old)
{
  this->size_ = old.size_;
  this->rooms_ = old.rooms_;
  old.size_ = 0;
  for (auto& r : old.rooms_)  r = nullptr;
  return *this;
}


// Creates some new rooms and store its pointers 

void Map::CreateRooms()
{
  rooms_.reserve(size_);
  for (int i = 0; i < size_; ++i) {
    rooms_.push_back(new Room(i));
  }
}

// Connects the rooms stored in vector

void Map::ConnectRooms()
{
  int halfsize = size_/2;
  Room* left_neighbor = nullptr;
  Room* right_neighbor = nullptr;

  // Connect rooms placed on center, outer and inner pathes
  
  for (int k = 0; k < halfsize; ++k) {
    if (k%2) {
      left_neighbor = &*rooms_[halfsize+k];
      right_neighbor = &*rooms_[k+1];
    }
    else {
      left_neighbor = &*rooms_[k+1];
      right_neighbor = &*rooms_[halfsize+k];
    }

    rooms_[k]->left_ = left_neighbor;
    rooms_[k]->right_ = right_neighbor;
    left_neighbor->back_ = rooms_[k];
    if (k != halfsize-1) {
      right_neighbor->back_ = rooms_[k];  // setted already when k was eq 0
    }
  }

  // Loop first and last rooms of center path

  rooms_[halfsize-1]->right_ = rooms_[0];
  rooms_[0]->back_ = rooms_[halfsize-1];

  // Connect rooms on outer and inner pathes

  for (int m = halfsize; m < size_; ++m) {
    if (m < size_-2) {
      rooms_[m]->right_ = rooms_[m+2];
      rooms_[m+2]->left_ = rooms_[m];
    }
  }
  
  // Loop first and last rooms on outer and inner pathes

  rooms_[halfsize]->left_ = rooms_[size_-2];
  rooms_[size_-2]->right_ = rooms_[halfsize];
  
  rooms_[halfsize+1]->left_ = rooms_[size_-1];
  rooms_[size_-1]->right_ = rooms_[halfsize+1];
}

Room* Map::GetRoom(int num) const
{
  return num >= size_ ? nullptr : rooms_[num];
}

// NON-MEMBER FUNCTIONS

std::ostream& operator<<(std::ostream& oss, const Map& cave)
{
  oss << "\nDebug cave:\n";
  for (auto i = 0; i < cave.GetSize(); ++i) {
    Room* r = cave.GetRoom(i);
    oss << r->num_ << ": " << r->persons_.size();
    oss << "\n";
  }
  return oss;
}

}  // namespace wumpus_game