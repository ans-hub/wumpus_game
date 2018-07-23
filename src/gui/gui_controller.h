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

class GuiController : public mvc_set::Controller
{
public:
  GuiController(Logic&, Windows&);
  ~GuiController() { }

  bool RunModel() override;
  void StopModel();

private:
  Logic&        model_;
  Windows&      gui_;

  // Commands for view used by gui through callbacks

  void CommandStart();
  void CommandContinue();
  void CommandLevel();
  void CommandAction(int);
  
  // Callbacks setters

  void SetLogicCommandsCallbacks();    // see note #1
  void SetLevelProcessingCallbacks();

  // Callbacks

  static void cb_start_button(void*, void*);
  static void cb_skip_button(void*, void*);
  static void cb_rooms_button(void*, void*);
  static void cb_continue_button(void*, void*);
};

}  // namespace wumpus_game

#endif  // GUI_CONTROLLER_H

// Note: controller sets callbacks which is based on the game logic. Callbacks
// that depends of managing windows are set in windows.o