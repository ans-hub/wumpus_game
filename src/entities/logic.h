// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#ifndef LOGIC_H
#define LOGIC_H

#include <cassert>
#include <string>

#include "entities/events.h"
#include "entities/helpers/logic_helpers.h"
#include "entities/helpers/map_helpers.h"
#include "entities/level.h"
#include "entities/subject.h"
#include "3rdparty/observable.h"
#include "settings/config.h"

namespace wumpus_game {

// make inherit from Abc Model

class Logic : public mvc_set::Observable<Event>
{
public:
  using Rooms = std::vector<int>;
  using SubjectID = Subject::ID;
  
  explicit Logic(const Config&);
  Logic(const Logic&) =delete;

  void NewLevel();
  void NewLevel(unsigned int num);
  void Turn(int, int);
  bool GameOver() const { return (game_over_cause_ != Subject::UNKNOWN); }
  Subject::ID GameOverCause() const { return game_over_cause_; }
  int CurrentLevel() const { return curr_level_; }
  const Level& GetLevel() const { return level_; }
  const Rooms& RoomsHistory() const { return rooms_history_; }
private:
  Level         level_;
  bool          player_turn_;
  Subject::ID   game_over_cause_;
  int           curr_level_;
  Rooms         rooms_history_;
  const Config& config_;

  void PlayerTurn(int, int);
  bool PlayerShot(int);
  bool PlayerMove(int);
  void WumpsTurn();
  void BatsTurn();
  void PitsTurn();
};

}  // namespace wumpus_game

#endif  // LOGIC_Р