// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ostream routines

#include "controller.h"

namespace wumpus_game {

bool CliController::RunModel()
{
  // model_.NewLevel(1);
  // do {
  //   int action { 1};
  //   int room {0};
  //   if (istream_ >> action >> room) {
  //     model_.Turn(action, room);
  //   }
  // } while(!model_.GameOver());
  // return true;

  if (!istream_) { return false; }
  
  model_.NewLevel(1);
  
  int room{-1};
  std::string action;

  do {
    if (istream_ >> action >> room) {
      if ((action == "m") || (action == "move")) {
        model_.Turn(0, room);
      }
      else if ((action == "s") || (action == "shot")) {
        model_.Turn(1, room);        
      }
      else if ((action == "q") || (action == "quit")) {
        return false;
      }
      else {
        model_.Turn(-1, room);
      }
    }
    else {
      istream_.clear();
      istream_.ignore(10000, '\n');
      model_.Turn(-1, room);
    }
  } while(!model_.GameOver());
  return true;
}

}  // namespace wumpus_game