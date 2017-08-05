// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Player class

#include "player.h"

namespace wumpus_game {

Player::Player(Map* cave, int arrows)
  : Subject(cave)
  , arrows_{arrows}
{
  type_ = Subject::PLAYER;
}

Player::Player(Player&& old)
  : Subject(std::move(old))
{
  arrows_ = old.arrows_;
}

Player& Player::operator=(Player&& old)
{
  Subject::operator=(std::move(old));
  this->arrows_ = old.arrows_;
  return *this;
}

Player::VSubjectsId Player::Feels() const
{
  VSubjectsId res;
  Room* next;

  next = curr_room_->left_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }

  next = curr_room_->right_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }
  
  next = curr_room_->back_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }
  return res;
}

bool Player::Shot()
{
  if (!arrows_) {
    return false;
  }
  else {
    --arrows_;
    return true;
  }
}

}  // namespace wumpus_game