// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Player class

#include "player.h"

namespace wumpus_game {

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

Subject::Person Player::Shot(int to_room) const
{
  int from_room = curr_room_->num_;

  if (!helpers::is_neighboring_rooms(to_room, from_room, cave_)) {
    return Person::EMPTY;
  }
  else {
    std::vector<const Subject*>& persons = cave_.GetRoom(to_room)->persons_;
    bool wump_shot {false};
    for (auto const& s:persons) {
      if (s->GetType() == Person::WUMP) {
        wump_shot = true;
      }
    }
    if (wump_shot) {
      return Person::WUMP;
    }
    else {
      return Person::EMPTY;
    }
  }
}

}  // namespace wumpus_game