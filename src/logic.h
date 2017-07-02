// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#ifndef LOGIC_H
#define LOGIC_H

#include <stdexcept>
#include <string>


#include "interaction.h"
#include "room.h"
#include "labyrinth.h"
#include "player.h"
#include "wump.h"
#include "bat.h"
#include "pit.h"
#include "helpers.h"

#include "ui/abc/observable.h"
#include "ui/message.h"

namespace wumpus_game {
 
class Logic 
: public mvc_set::Observable<mvc_set::Message, mvc_set::Message&, int&>  // see note #1 after code
{
public:
  typedef Subject::Person is;               // 

  enum class GameOverCause
  {
    NONE = 0,
    PLAYER,
    WUMP,
    PIT,
    USER
  };

  Logic();
  void Run();
  void StartGame();

private:

  Labyrinth cave_;
  Wump wump_;
  Bat bats_;
  Pit pit_;
  Player player_;
  bool game_over_cause_;
  

  // Realisation

  void PlayerTurn();
  void EnemyTurn();
  void IfBattle();
  void RebuildCave();

  // View methods

  void ShowNeighborRooms();
  void ShowPlayerFeels();
};

}  // namespace mvc_set

#endif  // LOGIC_Р

// Note #1 : Observer specialisation - int& - room number