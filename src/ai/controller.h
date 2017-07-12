// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ostream routines

#ifndef CLI_CTRL_H
#define CLI_CTRL_H

#include <istream>

#include "../3rdparty/observer.h"
#include "../events.h"
#include "../logic.h"

namespace wumpus_game {

class CliCtrl : public Controller
{
public:
  CliCtrl(std::istream& ist) : istream_{ist} { }
  ~CliCtrl() { }
  bool RunModel(Input& msg, int& n) override;
private:
  std::istream& istream_;
  Logic& 
};

namespace cli_helpers {

}  // namespace cli_helpers

}  // namespace wumpus_game

#endif  // CLI_CTRL_H