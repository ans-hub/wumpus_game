// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Map
//

#include "map.h"

namespace wumpus_game {

Map::Map(int base)
  : base_{base}
  , size_{base*4}   // todo: magic
  , rooms_{}
{
  CreateRooms();
  ConnectRooms();
}

Map::~Map()
{
  for (auto r : rooms_) {
    if (r) delete r;
  }
}

Map::Map(Map&& old)
  : base_{old.base_}
  , size_{old.size_}
  , rooms_{}
{
  old.base_ = 0;
  old.size_ = 0;
  rooms_.swap(old.rooms_);
}

Map& Map::operator=(Map&& old)
{
  this->base_ = old.base_;
  this->size_ = old.size_;
  this->rooms_.swap(old.rooms_);
  
  old.base_ = 0;
  old.size_ = 0;
  return *this;
}

void Map::CreateRooms()
{
  rooms_.reserve(size_);
  for (int i = 0; i < size_; ++i) {
    rooms_.push_back(new Room(i));
  }
}

void Map::ConnectRooms()
{
  int halfsize = size_/2;
  Room* left_neighbor = nullptr;
  Room* right_neighbor = nullptr;

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
      right_neighbor->back_ = rooms_[k];  // set already when k was eq 0
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

// HELPERS

std::ostream& operator<<(std::ostream& oss, const Map& cave)
{
  oss << "\nDebug cave:\n";
  for (auto i = 0; i < cave.GetSize(); ++i) {
    Room* r = cave.GetRoom(i);
    oss << r->num_ << ": " << r->subjects_.size();
    oss << "\n";
  }
  return oss;
}

std::vector<int> map_helpers::GetNeighboringRooms(int room_num, Map* cave)
{
  Room* room = cave->GetRoom(room_num);
  return { room->left_->num_
         , room->right_->num_
         , room->back_->num_
  };
}

// Returns bool if room num_1 and room num_2 is neighbors

bool map_helpers::IsNeighboringRooms(int num_1, int num_2, Map* cave)
{
  if (num_1 == num_2) return false;

  auto neighbors = GetNeighboringRooms(num_1, cave);
  auto result = std::find(std::begin(neighbors), std::end(neighbors), num_2);

  if (result != std::end(neighbors)) {
    return true;
  }
  return false;
}

}  // namespace wumpus_game