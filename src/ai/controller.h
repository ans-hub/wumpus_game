// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ai

#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include <iostream>

#include "3rdparty/controller.h"
#include "entities/logic.h"

namespace wumpus_game {

class AiController : public mvc_set::Controller
{
public:
  AiController(Logic& model, int level, int steps) 
    : Controller()
    , model_{model}
    , level_{level}
    , steps_{steps}
    { }
  ~AiController() { }
  bool RunModel() override;
private:
  Logic& model_;
  int level_;
  int steps_;
};

namespace ai_helpers {

}  // namespace ai_helpers

}  // namespace wumpus_game

#endif  // AI_CONTROLLER_H