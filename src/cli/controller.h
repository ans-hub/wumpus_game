// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ostream routines

#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include <iostream>

#include "../3rdparty/controller.h"
#include "../logic.h"

namespace wumpus_game {

class CliController : public mvc_set::Controller
{
public:
  CliController(std::istream& ist, Logic& model) 
    : Controller() 
    , istream_{ist}
    , model_{model} { }
  ~CliController() { }
  bool RunModel() override;
private:
  std::istream& istream_;
  Logic& model_;
};

namespace cli_helpers {

}  // namespace cli_helpers

}  // namespace wumpus_game

#endif  // CLI_CONTROLLER_H