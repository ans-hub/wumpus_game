// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#ifndef LOGIC_H
#define LOGIC_H

#include <cassert>
#include <string>

#include "events.h"
#include "helpers.h"
#include "entities/level.h"
#include "entities/subject.h"
#include "3rdparty/observable.h"

namespace wumpus_game {

// make inherit from Abc Model

class Logic : public mvc_set::Observable<Events>
{
public:
  Logic();
  Logic(const Logic&) =delete;

  void NewLevel(unsigned int);
  void Move(int);
  void Shot(int);
private:
  using Person = Subject::Person;

  Level   level_;
  Person  game_over_cause_;
};

}  // namespace wumpus_game

#endif  // LOGIC_Р