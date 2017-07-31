// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using gui, sets game callbacks

#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include "3rdparty/controller.h"
#include "gui/windows.h"
#include "gui/widgets/widget_room.h"
#include "entities/logic.h"

namespace wumpus_game {

class Fl_Widget;

class GuiController : public mvc_set::Controller
{
public:
  GuiController(Windows& gui, Logic& model);
  ~GuiController() { }
  bool RunModel() override;
  void StopModel();
  void CommandStart();
  void CommandContinue();
  void CommandLevel();
  void CommandAction(int);
private:
  Windows& gui_;
  Logic& model_;
  void SetGameCallbacks();    // see note #1
};

namespace gui_helpers {

  void cb_start_button(void*, void*);
  void cb_next_button(void*, void*);
  void cb_rooms_button(void*, void*);
  void cb_continue_button(void*, void*);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif  // GUI_CONTROLLER_H

// Note: controller sets callbacks which is based on the game logic. Callbacsk
// that depends of managing windows sets in windows.o