// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using gui

#include "controller.h"

namespace wumpus_game {

GuiController::GuiController(Windows& gui, Logic& model)
  : Controller() 
  , gui_{gui}
  , model_{model}
{
  // sets callbacks to gui_->wnd_main_;
}

bool GuiController::RunModel()
{
  // nothing
  return true;
}

}  // namespace wumpus_game