// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using gui

#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include "../3rdparty/controller.h"
#include "../logic.h"
#include "windows.h"

namespace wumpus_game {

class GuiController : public mvc_set::Controller
{
public:
  GuiController(Windows& gui, Logic& model);
  ~GuiController() { }
  bool RunModel() override;
private:
  Windows& gui_;
  Logic& model_;
};

namespace gui_helpers {

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif  // GUI_CONTROLLER_H