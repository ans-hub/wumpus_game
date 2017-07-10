// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Room class

#include "room.h"

namespace wumpus_game {

// Room::Room(Room&& old)
//   : num_{old.num_}
//   , left_{old.left_}
//   , right_{old.right_}
//   , back_{old.back_}
//   , persons_{std::move(old.persons_)}
// {
//   old.num_ = 0;
//   old.left_ = nullptr;
//   old.right_ = nullptr;
//   old.back_ = nullptr;
//   // for (auto v : old.persons_) {
//   //   v = nullptr;
//   // }
// }

bool Room::IsEmpty() const
{
  return (persons_.empty()) ? true : false;
}

}  // namespace wumpus_game