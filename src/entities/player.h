// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "subject.h"

namespace wumpus_game {

class Player : public Subject
{
public:
  explicit Player(const Map& cave)
  : Subject(cave)
  { type_ = Person::PLAYER; }
  ~Player() { }
  Player(Player&& old) : Subject(std::move(old)) { }
  
  Persons Feels() const;
  Person  Shot(int) const;
};

}  // namespace wumpus_game

#endif  // PLAYER_H