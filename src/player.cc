// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Player class

#include "player.h"

namespace anshub {

Player::Persons Player::Feels() const
{
  Persons res;
  Room* next;

  next = curr_room_->left_;
  for (auto const p : next->persons_) {
    res.push_back(p->GetType());
  }

  next = curr_room_->right_;
  for (auto const p : next->persons_) {
    res.push_back(p->GetType());
  }
  
  next = curr_room_->back_;
  for (auto const p : next->persons_) {
    res.push_back(p->GetType());
  }
  return res;
}

Subject::Person Player::Shot(int room) const
{
  if (!cave_.IsNeighbors (curr_room_->num_, room) ) {
    return EMPTY;
  }
  else {
    std::vector<const Subject*>& persons = cave_.GetRoom(room)->persons_;
    bool wump_shot {false};
    for (auto const& s:persons) {
      if (s->GetType() == WUMP) {
        wump_shot = true;
      }
    }
    if (wump_shot) {
      return WUMP;
    }
    else {
      return EMPTY;
    }
  }
}

}  // namespace anshub