// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#ifndef LOGIC_H
#define LOGIC_H

#include <stdexcept>
#include <string>
#include <algorithm>

#include "entities/room.h"
#include "entities/map.h"
#include "entities/player.h"
#include "entities/wump.h"
#include "entities/bat.h"
#include "entities/pit.h"


#include "3rdparty/observer.h"
#include "3rdparty/observable.h"
#include "events.h"
#include "helpers.h"

namespace wumpus_game {

class Logic
: public mvc_set::Observable<mvc_set::Show, mvc_set::Input&, int&>
{
public:
  typedef Subject::Person Person;

  Logic();
  void Run();
  void Rebuild();
  void StartGame();

  Level& level_;
  Person game_over_cause_;

private:
  void PlayerTurn();
  void EnemyTurn();
  void Battle();

  void PlayerDoShot(int);
  void PlayerDoMove(int);
  void GetUserInput(::mvc_set::Input&, int&);
};

}  // namespace wumpus_game

#endif  // LOGIC_Р

// Note #1 : Observer specialisation - int& - room number