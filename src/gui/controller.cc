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
  gui_.map_box_->SetCallback((void*)gui_helpers::cb_rooms_button);
  gui_.map_box_->SetCommand((void*)this);
 
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
  gui_.Show();
  return true;
}

void GuiController::StopModel()
{
  gui_.Close();
}

void GuiController::CommandStart()
{
  auto level = model_.CurrentLevel();
  if (level == -1) level = 0; // 0 level is so small far traingle
  model_.NewLevel(++level);
}

void GuiController::CommandAction(int room)
{
  auto e = Fl::event_button();
  if (e == FL_LEFT_MOUSE) {
    model_.Turn(0, room);
  }
  if (e == FL_RIGHT_MOUSE) {
    model_.Turn(1, room);
  }
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

void cb_rooms_button(void* b, void* c)
{
  ((GuiController*)c)->CommandAction(((RoomButton*)b)->num_);
}

}  // namespace gui_helpers

}  // namespace wumpus_game