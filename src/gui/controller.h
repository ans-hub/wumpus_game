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

class Fl_Widget;

class GuiController : public mvc_set::Controller
{
public:
  GuiController(Windows& gui, Logic& model);
  ~GuiController() { }
  bool RunModel() override;
  void StopModel();
  void CommandStart() { model_.NewLevel(1); }
private:
  Windows& gui_;
  Logic& model_;
};

namespace gui_helpers {

  void cb_start_button(void*, void*);
  void cb_quit_button(void*, void*);
  // void start_command();

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif  // GUI_CONTROLLER_H