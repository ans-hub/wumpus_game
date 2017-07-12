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
  auto* wnd = gui_.main_wnd_;
  wnd->btn_start_->callback(
    (Fl_Callback*)(gui_helpers::cb_start_button), (void*)this
  );

  wnd->btn_quit_->callback(
    (Fl_Callback*)(gui_helpers::cb_quit_button), (void*)this    
  );
}

bool GuiController::RunModel()
{
  // nothing
  gui_.Show();
  return true;
}

void GuiController::StopModel()
{
  gui_.Close();
}

namespace gui_helpers {

void cb_start_button(void*, void* c)
{
  ((GuiController*)c)->CommandStart();
}

void cb_quit_button(void*, void* c)
{
  ((GuiController*)c)->StopModel();
}

// void cb_shot_button(void*, void*)
// {

// }

// void cb_move_button(void*, void*)
// {

// }

// void start_command(Logic& model)
// {
//   model.NewLevel(1);
// }

// void shot_command()
// {

// }

// void move_command()
// {

// }

}  // namespace gui_helpers

}  // namespace wumpus_game