// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#ifndef LOGIC_H
#define LOGIC_H

#include <cassert>
#include <string>

#include "events.h"
#include "helpers/logic_helpers.h"
#include "helpers/entities_helpers.h"
#include "entities/level.h"
#include "entities/subject.h"
#include "3rdparty/observable.h"

namespace wumpus_game {

struct Request
{
  Request() : action_{}, room_{} { }
  void Set(int a, int r) { action_ = a; room_ = r; }
  void Clear() { action_ = -1; room_ = -1; }
  int action_;
  int room_;
};

// make inherit from Abc Model

class Logic : public mvc_set::Observable<Event>
{
public:
  friend struct CliView;
  using SubjectID = Subject::ID;
  
  Logic();
  Logic(const Logic&) =delete;

  void NewLevel(unsigned int);
  void Turn(int, int);
  bool GameOver() const { return (game_over_cause_ != Subject::UNKNOWN); }
  Subject::ID GameOverCause() const { return game_over_cause_; }
  // int CurrentLevel() const { return GameOver() ? -1 : curr_level_; }
  int CurrentLevel() const { return curr_level_; }
  const Request& CurrentRequest() const { return curr_request_; }
  const Level& GetLevel() const { return level_; }
protected:
  Level       level_;
  bool        player_turn_;
  Subject::ID game_over_cause_;
  int         curr_level_;
  Request     curr_request_;

  void PlayerTurn(int, int);
  bool PlayerShot(int);
  bool PlayerMove(int);
  void WumpsTurn();
  void BatsTurn();
  void PitsTurn();
};

}  // namespace wumpus_game

#endif  // LOGIC_Р